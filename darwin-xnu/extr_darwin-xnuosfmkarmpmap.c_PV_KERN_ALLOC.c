#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* pve_next; } ;
typedef  TYPE_1__ pv_entry_t ;

/* Variables and functions */
 TYPE_1__* PV_ENTRY_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_kern_reserve_alloc_stat ; 
 int /*<<< orphan*/  pmap_simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pv_kern_free_count ; 
 TYPE_1__* pv_kern_free_list ; 
 int /*<<< orphan*/  pv_kern_free_list_lock ; 

__attribute__((used)) static inline void	PV_KERN_ALLOC(pv_entry_t **pv_e) {
	assert(*pv_e == PV_ENTRY_NULL);
	pmap_simple_lock(&pv_kern_free_list_lock);

	if ((*pv_e = pv_kern_free_list) != 0) {
		pv_kern_free_list = (pv_entry_t *)(*pv_e)->pve_next;
		(*pv_e)->pve_next = PV_ENTRY_NULL;
		pv_kern_free_count--;
		pmap_kern_reserve_alloc_stat++;
	}

	pmap_simple_unlock(&pv_kern_free_list_lock);
}