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
 int FDT_ERR_BADMAGIC ; 
 scalar_t__ FDT_SW_MAGIC ; 
 scalar_t__ fdt_magic (void*) ; 

__attribute__((used)) static int _fdt_sw_check_header(void *fdt)
{
	if (fdt_magic(fdt) != FDT_SW_MAGIC)
		return -FDT_ERR_BADMAGIC;
	/* FIXME: should check more details about the header state */
	return 0;
}