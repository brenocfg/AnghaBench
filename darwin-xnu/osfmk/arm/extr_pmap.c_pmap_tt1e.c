#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  tt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tte; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 size_t tt1_index (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tt_entry_t *
pmap_tt1e(pmap_t pmap,
	 vm_map_address_t addr)
{
	/* Level 0 currently unused */
#if __ARM64_TWO_LEVEL_PMAP__
#pragma unused(pmap, addr)
	panic("pmap_tt1e called on a two level pmap");
	return (NULL);
#else
	return (&pmap->tte[tt1_index(pmap, addr)]);
#endif
}