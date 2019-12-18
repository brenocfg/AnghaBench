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
struct fdt_property {int /*<<< orphan*/  nameoff; } ;

/* Variables and functions */
 int FDT_ERR_INTERNAL ; 
 scalar_t__ _fdt_string_eq (void const*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int fdt_first_property_offset (void const*,int) ; 
 struct fdt_property* fdt_get_property_by_offset (void const*,int,int*) ; 
 int fdt_next_property_offset (void const*,int) ; 

const struct fdt_property *fdt_get_property_namelen(const void *fdt,
						    int offset,
						    const char *name,
						    int namelen, int *lenp)
{
	for (offset = fdt_first_property_offset(fdt, offset);
	     (offset >= 0);
	     (offset = fdt_next_property_offset(fdt, offset))) {
		const struct fdt_property *prop;

		if ((prop = fdt_get_property_by_offset(fdt, offset, lenp)) == 0) {
			offset = -FDT_ERR_INTERNAL;
			break;
		}
		if (_fdt_string_eq(fdt, fdt32_to_cpu(prop->nameoff),
				   name, namelen))
			return prop;
	}

	if (lenp)
		*lenp = offset;
	return NULL;
}