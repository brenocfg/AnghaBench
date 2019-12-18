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
 int __bitmap_parselist (char const*,int,int /*<<< orphan*/ ,unsigned long*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

int bitmap_parselist(const char *bp, unsigned long *maskp, int nmaskbits)
{
	char *nl  = strchr(bp, '\n');
	int len;

	if (nl)
		len = nl - bp;
	else
		len = strlen(bp);

	return __bitmap_parselist(bp, len, 0, maskp, nmaskbits);
}