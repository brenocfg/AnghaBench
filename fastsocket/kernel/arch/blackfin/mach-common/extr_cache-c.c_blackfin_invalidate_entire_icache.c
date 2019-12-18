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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int bfin_read_IMEM_CONTROL () ; 
 int /*<<< orphan*/  bfin_write_IMEM_CONTROL (int) ; 

void blackfin_invalidate_entire_icache(void)
{
	u32 imem = bfin_read_IMEM_CONTROL();
	bfin_write_IMEM_CONTROL(imem & ~0x4);
	SSYNC();
	bfin_write_IMEM_CONTROL(imem);
	SSYNC();
}