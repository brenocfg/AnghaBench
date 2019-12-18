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
 int TNMSZ ; 
 int TPFSZ ; 

__attribute__((used)) static char *
name_split(char *name, int len)
{
	char *start;

	/*
	 * check to see if the file name is small enough to fit in the name
	 * field. if so just return a pointer to the name.
	 */
	if (len <= TNMSZ)
		return(name);
	if (len > TPFSZ + TNMSZ)
		return(NULL);

	/*
	 * we start looking at the biggest sized piece that fits in the name
	 * field. We walk forward looking for a slash to split at. The idea is
	 * to find the biggest piece to fit in the name field (or the smallest
	 * prefix we can find)
	 */
	start = name + len - TNMSZ;
	while ((*start != '\0') && (*start != '/'))
		++start;

	/*
	 * if we hit the end of the string, this name cannot be split, so we
	 * cannot store this file.
	 */
	if (*start == '\0')
		return(NULL);
	len = start - name;

	/*
	 * NOTE: /str where the length of str == TNMSZ can not be stored under
	 * the p1003.1-1990 spec for ustar. We could force a prefix of / and
	 * the file would then expand on extract to //str. The len == 0 below
	 * makes this special case follow the spec to the letter.
	 */
	if ((len > TPFSZ) || (len == 0))
		return(NULL);

	/*
	 * ok have a split point, return it to the caller
	 */
	return(start);
}