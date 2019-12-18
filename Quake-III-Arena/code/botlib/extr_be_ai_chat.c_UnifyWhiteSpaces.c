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
 scalar_t__ IsWhiteSpace (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void UnifyWhiteSpaces(char *string)
{
	char *ptr, *oldptr;

	for (ptr = oldptr = string; *ptr; oldptr = ptr)
	{
		while(*ptr && IsWhiteSpace(*ptr)) ptr++;
		if (ptr > oldptr)
		{
			//if not at the start and not at the end of the string
			//write only one space
			if (oldptr > string && *ptr) *oldptr++ = ' ';
			//remove all other white spaces
			if (ptr > oldptr) memmove(oldptr, ptr, strlen(ptr)+1);
		} //end if
		while(*ptr && !IsWhiteSpace(*ptr)) ptr++;
	} //end while
}