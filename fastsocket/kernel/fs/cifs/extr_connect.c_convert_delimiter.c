#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void
convert_delimiter(char *path, char delim)
{
	int i;
	char old_delim;

	if (path == NULL)
		return;

	if (delim == '/')
		old_delim = '\\';
	else
		old_delim = '/';

	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == old_delim)
			path[i] = delim;
	}
}