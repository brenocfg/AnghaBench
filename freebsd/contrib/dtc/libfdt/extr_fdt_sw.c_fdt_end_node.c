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
typedef  int /*<<< orphan*/  fdt32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_END_NODE ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_SW_CHECK_HEADER (void*) ; 
 int /*<<< orphan*/  FDT_TAGSIZE ; 
 int /*<<< orphan*/ * _fdt_grab_space (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int /*<<< orphan*/ ) ; 

int fdt_end_node(void *fdt)
{
	fdt32_t *en;

	FDT_SW_CHECK_HEADER(fdt);

	en = _fdt_grab_space(fdt, FDT_TAGSIZE);
	if (! en)
		return -FDT_ERR_NOSPACE;

	*en = cpu_to_fdt32(FDT_END_NODE);
	return 0;
}