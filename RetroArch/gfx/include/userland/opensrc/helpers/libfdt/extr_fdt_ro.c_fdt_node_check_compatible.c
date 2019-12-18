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
 void* fdt_getprop (void const*,int,char*,int*) ; 
 scalar_t__ fdt_stringlist_contains (void const*,int,char const*) ; 

int fdt_node_check_compatible(const void *fdt, int nodeoffset,
			      const char *compatible)
{
	const void *prop;
	int len;

	prop = fdt_getprop(fdt, nodeoffset, "compatible", &len);
	if (!prop)
		return len;
	if (fdt_stringlist_contains(prop, len, compatible))
		return 0;
	else
		return 1;
}