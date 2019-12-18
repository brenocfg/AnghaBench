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
struct ledger_entry {scalar_t__ le_debit; scalar_t__ le_credit; int le_flags; } ;
typedef  TYPE_1__* ledger_t ;
typedef  scalar_t__ ledger_amount_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_VALID (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int LF_TRACK_CREDIT_ONLY ; 
 int /*<<< orphan*/  OSCompareAndSwap64 (scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lprintf (char*) ; 

kern_return_t
ledger_zero_balance(ledger_t ledger, int entry)
{
	struct ledger_entry *le;
	ledger_amount_t debit, credit;

	if (!ENTRY_VALID(ledger, entry))
		return (KERN_INVALID_VALUE);

	le = &ledger->l_entries[entry];

top:
	debit = le->le_debit;
	credit = le->le_credit;

	if (le->le_flags & LF_TRACK_CREDIT_ONLY) {
		assert(le->le_debit == 0);
		if (!OSCompareAndSwap64(credit, 0, &le->le_credit)) {
			goto top;
		}
		lprintf(("%p zeroed %lld->%lld\n", current_thread(), le->le_credit, 0));
	} else if (credit > debit) {
		if (!OSCompareAndSwap64(debit, credit, &le->le_debit))
			goto top;
		lprintf(("%p zeroed %lld->%lld\n", current_thread(), le->le_debit, le->le_credit));
	} else if (credit < debit) {
		if (!OSCompareAndSwap64(credit, debit, &le->le_credit))
			goto top;
		lprintf(("%p zeroed %lld->%lld\n", current_thread(), le->le_credit, le->le_debit));
	}

	return (KERN_SUCCESS);
}