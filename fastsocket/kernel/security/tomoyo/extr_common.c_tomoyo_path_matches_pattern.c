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
struct tomoyo_path_info {char* name; int const_len; scalar_t__ depth; int /*<<< orphan*/  is_patterned; } ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int const) ; 
 int /*<<< orphan*/  tomoyo_file_matches_to_pattern (char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  tomoyo_pathcmp (struct tomoyo_path_info const*,struct tomoyo_path_info const*) ; 

bool tomoyo_path_matches_pattern(const struct tomoyo_path_info *filename,
				 const struct tomoyo_path_info *pattern)
{
	/*
	  if (!filename || !pattern)
	  return false;
	*/
	const char *f = filename->name;
	const char *p = pattern->name;
	const int len = pattern->const_len;

	/* If @pattern doesn't contain pattern, I can use strcmp(). */
	if (!pattern->is_patterned)
		return !tomoyo_pathcmp(filename, pattern);
	/* Dont compare if the number of '/' differs. */
	if (filename->depth != pattern->depth)
		return false;
	/* Compare the initial length without patterns. */
	if (strncmp(f, p, len))
		return false;
	f += len;
	p += len;
	/* Main loop. Compare each directory component. */
	while (*f && *p) {
		const char *f_delimiter = strchr(f, '/');
		const char *p_delimiter = strchr(p, '/');
		if (!f_delimiter)
			f_delimiter = f + strlen(f);
		if (!p_delimiter)
			p_delimiter = p + strlen(p);
		if (!tomoyo_file_matches_to_pattern(f, f_delimiter,
						    p, p_delimiter))
			return false;
		f = f_delimiter;
		if (*f)
			f++;
		p = p_delimiter;
		if (*p)
			p++;
	}
	/* Ignore trailing "\*" and "\@" in @pattern. */
	while (*p == '\\' &&
	       (*(p + 1) == '*' || *(p + 1) == '@'))
		p += 2;
	return !*f && !*p;
}