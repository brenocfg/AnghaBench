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
struct fdt_property {void const* data; int /*<<< orphan*/  nameoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 struct fdt_property* fdt_get_property_by_offset (void const*,int,int*) ; 
 char* fdt_string (void const*,int /*<<< orphan*/ ) ; 

const void *fdt_getprop_by_offset(const void *fdt, int offset,
				  const char **namep, int *lenp)
{
	const struct fdt_property *prop;

	prop = fdt_get_property_by_offset(fdt, offset, lenp);
	if (!prop)
		return NULL;
	if (namep)
		*namep = fdt_string(fdt, fdt32_to_cpu(prop->nameoff));
	return prop->data;
}