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
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/ * ledger_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEDGER_CREATE_ACTIVE_ENTRIES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ledger_instantiate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * task_ledger_template ; 

__attribute__((used)) static pmap_t
pmap_create_wrapper() {
	pmap_t new_pmap = NULL;
	ledger_t ledger;
	assert(task_ledger_template != NULL);
	if ((ledger = ledger_instantiate(task_ledger_template, LEDGER_CREATE_ACTIVE_ENTRIES)) == NULL)
		return NULL;
        new_pmap = pmap_create(ledger, 0, FALSE);
	ledger_dereference(ledger);
	return new_pmap;
}