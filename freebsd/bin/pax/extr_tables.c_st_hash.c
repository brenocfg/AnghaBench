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
typedef  int u_int ;

/* Variables and functions */
 int MAXKEYLEN ; 

u_int
st_hash(char *name, int len, int tabsz)
{
	char *pt;
	char *dest;
	char *end;
	int i;
	u_int key = 0;
	int steps;
	int res;
	u_int val;

	/*
	 * only look at the tail up to MAXKEYLEN, we do not need to waste
	 * time here (remember these are pathnames, the tail is what will
	 * spread out the keys)
	 */
	if (len > MAXKEYLEN) {
		pt = &(name[len - MAXKEYLEN]);
		len = MAXKEYLEN;
	} else
		pt = name;

	/*
	 * calculate the number of u_int size steps in the string and if
	 * there is a runt to deal with
	 */
	steps = len/sizeof(u_int);
	res = len % sizeof(u_int);

	/*
	 * add up the value of the string in unsigned integer sized pieces
	 * too bad we cannot have unsigned int aligned strings, then we
	 * could avoid the expensive copy.
	 */
	for (i = 0; i < steps; ++i) {
		end = pt + sizeof(u_int);
		dest = (char *)&val;
		while (pt < end)
			*dest++ = *pt++;
		key += val;
	}

	/*
	 * add in the runt padded with zero to the right
	 */
	if (res) {
		val = 0;
		end = pt + res;
		dest = (char *)&val;
		while (pt < end)
			*dest++ = *pt++;
		key += val;
	}

	/*
	 * return the result mod the table size
	 */
	return(key % tabsz);
}