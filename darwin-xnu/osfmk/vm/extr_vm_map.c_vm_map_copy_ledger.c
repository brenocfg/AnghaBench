#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* task_t ;
typedef  scalar_t__ ledger_amount_t ;
struct TYPE_6__ {int /*<<< orphan*/  ledger; TYPE_1__* map; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_corpse_footprint; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_credit (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ledger_debit (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ledger_disable_panic_on_negative (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ledger_get_balance (int /*<<< orphan*/ ,int,scalar_t__*) ; 

void
vm_map_copy_ledger(
	task_t	old_task,
	task_t	new_task,
	int	ledger_entry)
{
	ledger_amount_t	old_balance, new_balance, delta;

	assert(new_task->map->has_corpse_footprint);
	if (!new_task->map->has_corpse_footprint)
		return;

	/* turn off sanity checks for the ledger we're about to mess with */
	ledger_disable_panic_on_negative(new_task->ledger,
					 ledger_entry);

	/* adjust "new_task" to match "old_task" */
	ledger_get_balance(old_task->ledger,
			   ledger_entry,
			   &old_balance);
	ledger_get_balance(new_task->ledger,
			   ledger_entry,
			   &new_balance);
	if (new_balance == old_balance) {
		/* new == old: done */
	} else if (new_balance > old_balance) {
		/* new > old ==> new -= new - old */
		delta = new_balance - old_balance;
		ledger_debit(new_task->ledger,
			     ledger_entry,
			     delta);
	} else {
		/* new < old ==> new += old - new */
		delta = old_balance - new_balance;
		ledger_credit(new_task->ledger,
			      ledger_entry,
			      delta);
	}
}