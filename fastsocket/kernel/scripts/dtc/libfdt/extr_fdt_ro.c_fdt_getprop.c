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
struct fdt_property {void const* data; } ;

/* Variables and functions */
 struct fdt_property* fdt_get_property (void const*,int,char const*,int*) ; 

const void *fdt_getprop(const void *fdt, int nodeoffset,
		  const char *name, int *lenp)
{
	const struct fdt_property *prop;

	prop = fdt_get_property(fdt, nodeoffset, name, lenp);
	if (! prop)
		return NULL;

	return prop->data;
}