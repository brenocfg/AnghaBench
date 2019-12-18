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
 int FDT_ERR_BADVALUE ; 
 int FDT_ERR_NOTFOUND ; 
 char* fdt_getprop (void const*,int,char const*,int*) ; 
 int strnlen (char const*,int) ; 

const char *fdt_stringlist_get(const void *fdt, int nodeoffset,
			       const char *property, int idx,
			       int *lenp)
{
	const char *list, *end;
	int length;

	list = fdt_getprop(fdt, nodeoffset, property, &length);
	if (!list) {
		if (lenp)
			*lenp = length;

		return NULL;
	}

	end = list + length;

	while (list < end) {
		length = strnlen(list, end - list) + 1;

		/* Abort if the last string isn't properly NUL-terminated. */
		if (list + length > end) {
			if (lenp)
				*lenp = -FDT_ERR_BADVALUE;

			return NULL;
		}

		if (idx == 0) {
			if (lenp)
				*lenp = length - 1;

			return list;
		}

		list += length;
		idx--;
	}

	if (lenp)
		*lenp = -FDT_ERR_NOTFOUND;

	return NULL;
}