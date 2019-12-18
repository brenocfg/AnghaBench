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
struct thash_data {void* rid; void* vadr; void* itir; void* page_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline void vcpu_set_tr(struct thash_data *trp, u64 pte, u64 itir,
		u64 va, u64 rid)
{
	trp->page_flags = pte;
	trp->itir = itir;
	trp->vadr = va;
	trp->rid = rid;
}