/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:50:43 by tlize             #+#    #+#             */
/*   Updated: 2024/12/09 15:21:49 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_store(int fd, char *memory)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(memory, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		memory = ft_strjoin(memory, buffer);
	}
	free(buffer);
	return (memory);
}

static char	*extract_line(char *storage)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!storage || !*storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(i + (storage[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] == '\n')
	{
		line[i] = storage[i];
		i ++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*trim_storage(char *storage)
{
	size_t	i;
	size_t	j;
	char	*new_storage;

	i = 0;
	j = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(ft_strlen(storage) - i);
	if (!new_storage)
		return (NULL);
	i++;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	memory = read_store(fd, memory);
	if (!memory)
		return (NULL);
	current_line = extract_line(memory);
	memory = trim_storage(memory);
	return (current_line);
}
