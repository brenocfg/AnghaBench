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
struct ledger_entry {int /*<<< orphan*/  le_debit; int /*<<< orphan*/  le_credit; } ;
typedef  TYPE_1__* ledger_t ;
typedef  int /*<<< orphan*/  ledger_amount_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_VALID (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 

kern_return_t
ledger_get_entries(ledger_t ledger, int entry, ledger_amount_t *credit,
    ledger_amount_t *debit)
{
	struct ledger_entry *le;

	if (!ENTRY_VALID(ledger, entry))
		return (KERN_INVALID_ARGUMENT);

	le = &ledger->l_entries[entry];

	*credit = le->le_credit;
	*debit = le->le_debit;

	return (KERN_SUCCESS);
}