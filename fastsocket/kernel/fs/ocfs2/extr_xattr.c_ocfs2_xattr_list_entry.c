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
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int ocfs2_xattr_list_entry(char *buffer, size_t size,
				  size_t *result, const char *prefix,
				  const char *name, int name_len)
{
	char *p = buffer + *result;
	int prefix_len = strlen(prefix);
	int total_len = prefix_len + name_len + 1;

	*result += total_len;

	/* we are just looking for how big our buffer needs to be */
	if (!size)
		return 0;

	if (*result > size)
		return -ERANGE;

	memcpy(p, prefix, prefix_len);
	memcpy(p + prefix_len, name, name_len);
	p[prefix_len + name_len] = '\0';

	return 0;
}