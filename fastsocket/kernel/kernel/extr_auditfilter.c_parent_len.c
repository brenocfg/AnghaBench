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
 int strlen (char const*) ; 

int parent_len(const char *path)
{
	int plen;
	const char *p;

	plen = strlen(path);

	if (plen == 0)
		return plen;

	/* disregard trailing slashes */
	p = path + plen - 1;
	while ((*p == '/') && (p > path))
		p--;

	/* walk backward until we find the next slash or hit beginning */
	while ((*p != '/') && (p > path))
		p--;

	/* did we find a slash? Then increment to include it in path */
	if (*p == '/')
		p++;

	return p - path;
}