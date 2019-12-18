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
typedef  void* u64 ;

/* Variables and functions */
 void* shadow_notrap_nonpresent_pte ; 
 void* shadow_trap_nonpresent_pte ; 

void kvm_mmu_set_nonpresent_ptes(u64 trap_pte, u64 notrap_pte)
{
	shadow_trap_nonpresent_pte = trap_pte;
	shadow_notrap_nonpresent_pte = notrap_pte;
}