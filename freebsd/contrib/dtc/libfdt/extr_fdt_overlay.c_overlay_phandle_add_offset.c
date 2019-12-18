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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int FDT_ERR_BADPHANDLE ; 
 int FDT_ERR_NOPHANDLES ; 
 scalar_t__ fdt32_to_cpu (scalar_t__ const) ; 
 scalar_t__* fdt_getprop (void*,int,char const*,int*) ; 
 int fdt_setprop_inplace_u32 (void*,int,char const*,scalar_t__) ; 

__attribute__((used)) static int overlay_phandle_add_offset(void *fdt, int node,
				      const char *name, uint32_t delta)
{
	const uint32_t *val;
	uint32_t adj_val;
	int len;

	val = fdt_getprop(fdt, node, name, &len);
	if (!val)
		return len;

	if (len != sizeof(*val))
		return -FDT_ERR_BADPHANDLE;

	adj_val = fdt32_to_cpu(*val);
	if ((adj_val + delta) < adj_val)
		return -FDT_ERR_NOPHANDLES;

	adj_val += delta;
	if (adj_val == (uint32_t)-1)
		return -FDT_ERR_NOPHANDLES;

	return fdt_setprop_inplace_u32(fdt, node, name, adj_val);
}