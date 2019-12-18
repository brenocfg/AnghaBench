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
 int chomp_trailing_dir_sep (char const*,int) ; 
 scalar_t__ is_dir_sep (char const) ; 
 int strlen (char const*) ; 
 char* strndup (char const*,int) ; 

char *strip_path_suffix(const char *path, const char *suffix)
{
	int path_len = strlen(path), suffix_len = strlen(suffix);

	while (suffix_len) {
		if (!path_len)
			return NULL;

		if (is_dir_sep(path[path_len - 1])) {
			if (!is_dir_sep(suffix[suffix_len - 1]))
				return NULL;
			path_len = chomp_trailing_dir_sep(path, path_len);
			suffix_len = chomp_trailing_dir_sep(suffix, suffix_len);
		}
		else if (path[--path_len] != suffix[--suffix_len])
			return NULL;
	}

	if (path_len && !is_dir_sep(path[path_len - 1]))
		return NULL;
	return strndup(path, chomp_trailing_dir_sep(path, path_len));
}