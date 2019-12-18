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
 void const* _fdt_offset_ptr (void const*,int) ; 
 int fdt_off_dt_struct (void const*) ; 
 int fdt_size_dt_struct (void const*) ; 
 unsigned int fdt_totalsize (void const*) ; 
 int fdt_version (void const*) ; 

const void *fdt_offset_ptr(const void *fdt, int offset, unsigned int len)
{
	unsigned absoffset = offset + fdt_off_dt_struct(fdt);

	if ((absoffset < offset)
	    || ((absoffset + len) < absoffset)
	    || (absoffset + len) > fdt_totalsize(fdt))
		return NULL;

	if (fdt_version(fdt) >= 0x11)
		if (((offset + len) < offset)
		    || ((offset + len) > fdt_size_dt_struct(fdt)))
			return NULL;

	return _fdt_offset_ptr(fdt, offset);
}