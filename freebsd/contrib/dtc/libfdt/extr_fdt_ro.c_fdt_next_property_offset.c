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
 int _fdt_check_prop_offset (void const*,int) ; 
 int _nextprop (void const*,int) ; 

int fdt_next_property_offset(const void *fdt, int offset)
{
	if ((offset = _fdt_check_prop_offset(fdt, offset)) < 0)
		return offset;

	return _nextprop(fdt, offset);
}