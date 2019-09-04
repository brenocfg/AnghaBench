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
struct ledger_entry {int le_flags; scalar_t__ le_debit; scalar_t__ le_credit; scalar_t__ le_warn_level; } ;
typedef  scalar_t__ ledger_amount_t ;

/* Variables and functions */
 scalar_t__ LEDGER_LIMIT_INFINITY ; 
 int LF_TRACK_CREDIT_ONLY ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int
warn_level_exceeded(struct ledger_entry *le)
{
	ledger_amount_t balance;

	if (le->le_flags & LF_TRACK_CREDIT_ONLY) {
		assert(le->le_debit == 0);
	} else {
		assert((le->le_credit >= 0) && (le->le_debit >= 0));
	}

	/*
	 * XXX - Currently, we only support warnings for ledgers which
	 * use positive limits.
	 */
	balance = le->le_credit - le->le_debit;
	if ((le->le_warn_level != LEDGER_LIMIT_INFINITY) && (balance > le->le_warn_level))
		return (1);
	return (0);
}