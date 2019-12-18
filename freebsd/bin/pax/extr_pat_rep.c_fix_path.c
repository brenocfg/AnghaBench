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
 int PAXPATHLEN ; 
 int /*<<< orphan*/  paxwarn (int,char*,char*,char*) ; 

__attribute__((used)) static int
fix_path( char *or_name, int *or_len, char *dir_name, int dir_len)
{
	char *src;
	char *dest;
	char *start;
	int len;

	/*
	 * we shift the or_name to the right enough to tack in the dir_name
	 * at the front. We make sure we have enough space for it all before
	 * we start. since dest always ends in a slash, we skip of or_name
	 * if it also starts with one.
	 */
	start = or_name;
	src = start + *or_len;
	dest = src + dir_len;
	if (*start == '/') {
		++start;
		--dest;
	}
	if ((len = dest - or_name) > PAXPATHLEN) {
		paxwarn(1, "File name %s/%s, too long", dir_name, start);
		return(-1);
	}
	*or_len = len;

	/*
	 * enough space, shift
	 */
	while (src >= start)
		*dest-- = *src--;
	src = dir_name + dir_len - 1;

	/*
	 * splice in the destination directory name
	 */
	while (src >= dir_name)
		*dest-- = *src--;

	*(or_name + len) = '\0';
	return(0);
}