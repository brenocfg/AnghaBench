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
typedef  int u_int ;
struct sdram_params {int refresh; int rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int ns_to_cycles (int,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  sdram_set_refresh (int) ; 

__attribute__((used)) static void
sdram_update_refresh(u_int cpu_khz, struct sdram_params *sdram)
{
	u_int ns_row = (sdram->refresh * 1000) >> sdram->rows;
	u_int dri = ns_to_cycles(ns_row, cpu_khz / 2) / 32;

#ifdef DEBUG
	mdelay(250);
	printk("new dri value = %d\n", dri);
#endif

	sdram_set_refresh(dri);
}