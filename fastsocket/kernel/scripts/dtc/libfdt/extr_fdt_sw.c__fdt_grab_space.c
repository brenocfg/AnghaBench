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
 int fdt_off_dt_struct (void*) ; 
 void* fdt_offset_ptr_w (void*,int,int) ; 
 int /*<<< orphan*/  fdt_set_size_dt_struct (void*,int) ; 
 int fdt_size_dt_strings (void*) ; 
 int fdt_size_dt_struct (void*) ; 
 int fdt_totalsize (void*) ; 

__attribute__((used)) static void *_fdt_grab_space(void *fdt, int len)
{
	int offset = fdt_size_dt_struct(fdt);
	int spaceleft;

	spaceleft = fdt_totalsize(fdt) - fdt_off_dt_struct(fdt)
		- fdt_size_dt_strings(fdt);

	if ((offset + len < offset) || (offset + len > spaceleft))
		return NULL;

	fdt_set_size_dt_struct(fdt, offset + len);
	return fdt_offset_ptr_w(fdt, offset, len);
}