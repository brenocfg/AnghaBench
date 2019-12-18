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
struct fdt_property {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int _fdt_check_prop_offset (void const*,int) ; 
 struct fdt_property* _fdt_offset_ptr (void const*,int) ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 

const struct fdt_property *fdt_get_property_by_offset(const void *fdt,
						      int offset,
						      int *lenp)
{
	int err;
	const struct fdt_property *prop;

	if ((err = _fdt_check_prop_offset(fdt, offset)) < 0) {
		if (lenp)
			*lenp = err;
		return NULL;
	}

	prop = _fdt_offset_ptr(fdt, offset);

	if (lenp)
		*lenp = fdt32_to_cpu(prop->len);

	return prop;
}