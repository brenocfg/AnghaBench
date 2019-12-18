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
typedef  TYPE_1__* pmap_t ;
struct TYPE_5__ {scalar_t__ pm_eptp; } ;

/* Variables and functions */
 int PMAP_CREATE_64BIT ; 
 int PMAP_CREATE_EPT ; 
 TYPE_1__* PMAP_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  get_task_ledger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ept_pmap (TYPE_1__*) ; 
 TYPE_1__* pmap_create_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
hv_ept_pmap_create(void **ept_pmap, void **eptp)
{
	pmap_t p;

	if ((ept_pmap == NULL) || (eptp == NULL)) {
		return;
	}

	p = pmap_create_options(get_task_ledger(current_task()), 0, (PMAP_CREATE_64BIT | PMAP_CREATE_EPT));
	if (p == PMAP_NULL) {
		*ept_pmap = NULL;
		*eptp = NULL;
		return;
	}

	assert(is_ept_pmap(p));

	*ept_pmap = (void*)p;
	*eptp = (void*)(p->pm_eptp);
	return;
}