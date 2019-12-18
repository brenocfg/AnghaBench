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
struct fdt_property {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _fdt_nop_region (struct fdt_property*,int) ; 
 struct fdt_property* fdt_get_property_w (void*,int,char const*,int*) ; 

int fdt_nop_property(void *fdt, int nodeoffset, const char *name)
{
	struct fdt_property *prop;
	int len;

	prop = fdt_get_property_w(fdt, nodeoffset, name, &len);
	if (! prop)
		return len;

	_fdt_nop_region(prop, len + sizeof(*prop));

	return 0;
}