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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RWNA ; 
 int /*<<< orphan*/  arm_vm_page_granular_prot (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
arm_vm_page_granular_RWNX(vm_offset_t start, unsigned long size, bool force_page_granule)
{
	arm_vm_page_granular_prot(start, size, 0, 1, AP_RWNA, 1, force_page_granule);
}