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
 int /*<<< orphan*/  pmap_simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_simple_unlock (int /*<<< orphan*/ *) ; 
 int pv_kern_free_count ; 
 TYPE_1__* pv_kern_free_list ; 
 int /*<<< orphan*/  pv_kern_free_list_lock ; 

__attribute__((used)) static inline void	PV_KERN_FREE_LIST(pv_entry_t *pv_eh, pv_entry_t *pv_et, int pv_cnt) {
	pmap_simple_lock(&pv_kern_free_list_lock);
	pv_et->pve_next = pv_kern_free_list;
	pv_kern_free_list = pv_eh;
	pv_kern_free_count += pv_cnt;
	pmap_simple_unlock(&pv_kern_free_list_lock);
}