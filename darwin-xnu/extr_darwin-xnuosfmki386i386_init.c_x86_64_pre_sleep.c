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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ID_MAP_VTOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IdlePML4 ; 
 size_t KERNEL_PML4_INDEX ; 
 int /*<<< orphan*/  get_cr3_raw () ; 
 int /*<<< orphan*/  set_cr3_raw (int /*<<< orphan*/ ) ; 

uint64_t
x86_64_pre_sleep(void)
{
	IdlePML4[0] = IdlePML4[KERNEL_PML4_INDEX];
	uint64_t oldcr3 = get_cr3_raw();
	set_cr3_raw((uint32_t) (uintptr_t)ID_MAP_VTOP(IdlePML4));
	return oldcr3;
}