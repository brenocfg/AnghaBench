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
struct ledger_entry {int /*<<< orphan*/  le_debit; int /*<<< orphan*/  le_credit; } ;
typedef  TYPE_1__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {scalar_t__ l_template; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 scalar_t__ ENTRY_VALID (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  OSAddAtomic64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

kern_return_t
ledger_rollup_entry(ledger_t to_ledger, ledger_t from_ledger, int entry)
{
	struct ledger_entry *from_le, *to_le;

	assert(to_ledger->l_template == from_ledger->l_template);
	if (ENTRY_VALID(from_ledger, entry) && ENTRY_VALID(to_ledger, entry)) {
		from_le = &from_ledger->l_entries[entry];
		to_le   =   &to_ledger->l_entries[entry];
		OSAddAtomic64(from_le->le_credit, &to_le->le_credit);
		OSAddAtomic64(from_le->le_debit,  &to_le->le_debit);
	}

	return (KERN_SUCCESS);
}