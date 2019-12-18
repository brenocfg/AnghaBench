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
struct reiserfs_key {int dummy; } ;
struct cpu_key {int dummy; } ;

/* Variables and functions */
 int ITEM_FOUND ; 
 int ITEM_NOT_FOUND ; 
 int comp_keys (struct reiserfs_key*,struct cpu_key*) ; 

__attribute__((used)) static inline int bin_search(const void *key,	/* Key to search for. */
			     const void *base,	/* First item in the array. */
			     int num,	/* Number of items in the array. */
			     int width,	/* Item size in the array.
					   searched. Lest the reader be
					   confused, note that this is crafted
					   as a general function, and when it
					   is applied specifically to the array
					   of item headers in a node, width
					   is actually the item header size not
					   the item size. */
			     int *pos /* Number of the searched for element. */
    )
{
	int rbound, lbound, j;

	for (j = ((rbound = num - 1) + (lbound = 0)) / 2;
	     lbound <= rbound; j = (rbound + lbound) / 2)
		switch (comp_keys
			((struct reiserfs_key *)((char *)base + j * width),
			 (struct cpu_key *)key)) {
		case -1:
			lbound = j + 1;
			continue;
		case 1:
			rbound = j - 1;
			continue;
		case 0:
			*pos = j;
			return ITEM_FOUND;	/* Key found in the array.  */
		}

	/* bin_search did not find given key, it returns position of key,
	   that is minimal and greater than the given one. */
	*pos = lbound;
	return ITEM_NOT_FOUND;
}