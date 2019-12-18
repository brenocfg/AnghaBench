#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int asid; } ;

/* Variables and functions */
 int TLBI_ASID_SHIFT ; 
 int /*<<< orphan*/  flush_core_tlb_asid (int) ; 

__attribute__((used)) static void
pmap_flush_core_tlb_asid(pmap_t pmap)
{
#if (__ARM_VMSA__ == 7)
	flush_core_tlb_asid(pmap->asid);
#else
	flush_core_tlb_asid(((uint64_t) pmap->asid) << TLBI_ASID_SHIFT);
#endif
}