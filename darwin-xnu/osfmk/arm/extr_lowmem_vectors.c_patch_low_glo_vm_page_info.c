#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_2__ {void* lgPmapMemFirstppnum; void* lgPmapMemEndAddr; void* lgPmapMemStartAddr; } ;

/* Variables and functions */
 TYPE_1__ lowGlo ; 

void patch_low_glo_vm_page_info(void * start_addr, void * end_addr, uint32_t first_ppnum)
{
	lowGlo.lgPmapMemStartAddr = (uint32_t)start_addr;
	lowGlo.lgPmapMemEndAddr = (uint32_t)end_addr;
	lowGlo.lgPmapMemFirstppnum = first_ppnum;
}