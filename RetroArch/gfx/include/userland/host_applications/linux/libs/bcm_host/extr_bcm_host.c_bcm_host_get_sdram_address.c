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
 unsigned int get_dt_ranges (char*,int) ; 

unsigned bcm_host_get_sdram_address(void)
{
   unsigned address = get_dt_ranges("/proc/device-tree/axi/vc_mem/reg", 8);
   return address == ~0 ? 0x40000000 : address;
}