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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ memory_size; } ;

/* Variables and functions */
 TYPE_1__ machine_info ; 
 scalar_t__ mem_size ; 

void
machine_conf(void)
{
	/*
	 * This is known to be inaccurate. mem_size should always be capped at 2 GB
	 */
	machine_info.memory_size = (uint32_t)mem_size;
}