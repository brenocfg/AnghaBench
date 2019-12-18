#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ l_template; int l_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ledger_rollup_entry (TYPE_1__*,TYPE_1__*,int) ; 

kern_return_t
ledger_rollup(ledger_t to_ledger, ledger_t from_ledger)
{
	int i;

	assert(to_ledger->l_template == from_ledger->l_template);

	for (i = 0; i < to_ledger->l_size; i++) {
		ledger_rollup_entry(to_ledger, from_ledger, i);
	}

	return (KERN_SUCCESS);
}