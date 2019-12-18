#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct TYPE_5__ {scalar_t__ le_last_refill; scalar_t__ le_refill_period; } ;
struct TYPE_4__ {scalar_t__ le_lifetime_max; scalar_t__ le_interval_max; } ;
struct TYPE_6__ {TYPE_2__ le_refill; TYPE_1__ _le_max; } ;
struct ledger_entry {int le_flags; scalar_t__ le_credit; scalar_t__ le_debit; TYPE_3__ _le; } ;
typedef  int /*<<< orphan*/  ledger_t ;
typedef  scalar_t__ ledger_amount_t ;

/* Variables and functions */
 int LEDGER_ACTION_BLOCK ; 
 int LEDGER_ACTION_CALLBACK ; 
 int LF_CALLED_BACK ; 
 int LF_PANIC_ON_NEGATIVE ; 
 int LF_REFILL_SCHEDULED ; 
 int LF_TRACKING_MAX ; 
 int LF_WAKE_NEEDED ; 
 int LF_WARNED ; 
 int /*<<< orphan*/  act_set_astledger_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ entry_get_callback (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ledger_limit_entry_wakeup (struct ledger_entry*) ; 
 int /*<<< orphan*/  ledger_refill (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ limit_exceeded (struct ledger_entry*) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int,struct ledger_entry*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ warn_level_exceeded (struct ledger_entry*) ; 

void
ledger_entry_check_new_balance(thread_t thread, ledger_t ledger,
                               int entry, struct ledger_entry *le)
{
	if (le->le_flags & LF_TRACKING_MAX) {
		ledger_amount_t balance = le->le_credit - le->le_debit;

		if (balance > le->_le._le_max.le_lifetime_max){
			le->_le._le_max.le_lifetime_max = balance;
		}

#if CONFIG_LEDGER_INTERVAL_MAX
		if (balance > le->_le._le_max.le_interval_max) {
			le->_le._le_max.le_interval_max = balance;
		}
#endif /* LEDGER_CONFIG_INTERVAL_MAX */
	}

	/* Check to see whether we're due a refill */
	if (le->le_flags & LF_REFILL_SCHEDULED) {
		assert(!(le->le_flags & LF_TRACKING_MAX));

		uint64_t now = mach_absolute_time();
		if ((now - le->_le.le_refill.le_last_refill) > le->_le.le_refill.le_refill_period)
			ledger_refill(now, ledger, entry);
	}

	if (limit_exceeded(le)) {
		/*
		 * We've exceeded the limit for this entry.  There
		 * are several possible ways to handle it.  We can block,
		 * we can execute a callback, or we can ignore it.  In
		 * either of the first two cases, we want to set the AST
		 * flag so we can take the appropriate action just before
		 * leaving the kernel.  The one caveat is that if we have
		 * already called the callback, we don't want to do it
		 * again until it gets rearmed.
		 */
		if ((le->le_flags & LEDGER_ACTION_BLOCK) ||
		    (!(le->le_flags & LF_CALLED_BACK) &&
		    entry_get_callback(ledger, entry))) {
			act_set_astledger_async(thread);
		}
	} else {
		/*
		 * The balance on the account is below the limit.
		 *
		 * If there are any threads blocked on this entry, now would
		 * be a good time to wake them up.
		 */
		if (le->le_flags & LF_WAKE_NEEDED)
			ledger_limit_entry_wakeup(le);

		if (le->le_flags & LEDGER_ACTION_CALLBACK) {
			/*
			 * Client has requested that a callback be invoked whenever
			 * the ledger's balance crosses into or out of the warning
			 * level.
			 */
		 	if (warn_level_exceeded(le)) {
		 		/*
		 		 * This ledger's balance is above the warning level.
		 		 */ 
		 		if ((le->le_flags & LF_WARNED) == 0) {
		 			/*
		 			 * If we are above the warning level and
		 			 * have not yet invoked the callback,
		 			 * set the AST so it can be done before returning
		 			 * to userland.
		 			 */
					act_set_astledger_async(thread);
				}
			} else {
				/*
				 * This ledger's balance is below the warning level.
				 */
		 		if (le->le_flags & LF_WARNED) {
					/*
					 * If we are below the warning level and
					 * the LF_WARNED flag is still set, we need
					 * to invoke the callback to let the client
					 * know the ledger balance is now back below
					 * the warning level.
					 */
					act_set_astledger_async(thread);
				}
			}
		}
	}

	if ((le->le_flags & LF_PANIC_ON_NEGATIVE) &&
	    (le->le_credit < le->le_debit)) {
		panic("ledger_entry_check_new_balance(%p,%d): negative ledger %p credit:%lld debit:%lld balance:%lld\n",
		      ledger, entry, le,
		      le->le_credit,
		      le->le_debit,
		      le->le_credit - le->le_debit);
	}
}