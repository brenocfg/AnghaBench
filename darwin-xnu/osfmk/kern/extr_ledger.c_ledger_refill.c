#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ le_last_refill; scalar_t__ le_refill_period; } ;
struct TYPE_7__ {TYPE_1__ le_refill; } ;
struct ledger_entry {scalar_t__ le_limit; int le_flags; scalar_t__ le_debit; scalar_t__ le_credit; TYPE_2__ _le; } ;
typedef  TYPE_3__* ledger_t ;
typedef  scalar_t__ ledger_amount_t ;
struct TYPE_8__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 scalar_t__ LEDGER_LIMIT_INFINITY ; 
 int LF_REFILL_INPROGRESS ; 
 int LF_TRACK_CREDIT_ONLY ; 
 int /*<<< orphan*/  OSAddAtomic64 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,scalar_t__,TYPE_3__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  flag_clear (int*,int) ; 
 int flag_set (int*,int) ; 
 int /*<<< orphan*/  ledger_limit_entry_wakeup (struct ledger_entry*) ; 
 int /*<<< orphan*/  limit_exceeded (struct ledger_entry*) ; 
 int /*<<< orphan*/  lprintf (char*) ; 

__attribute__((used)) static void
ledger_refill(uint64_t now, ledger_t ledger, int entry)
{
	uint64_t elapsed, period, periods;
	struct ledger_entry *le;
	ledger_amount_t balance, due;

	assert(entry >= 0 && entry < ledger->l_size);

	le = &ledger->l_entries[entry];

	assert(le->le_limit != LEDGER_LIMIT_INFINITY);

	if (le->le_flags & LF_TRACK_CREDIT_ONLY) {
		assert(le->le_debit == 0);
		return;
	}

	/*
	 * If another thread is handling the refill already, we're not
	 * needed.
	 */
	if (flag_set(&le->le_flags, LF_REFILL_INPROGRESS) & LF_REFILL_INPROGRESS) {
		return;
	}

	/*
	 * If the timestamp we're about to use to refill is older than the
	 * last refill, then someone else has already refilled this ledger
	 * and there's nothing for us to do here.
	 */
	if (now <= le->_le.le_refill.le_last_refill) {
		flag_clear(&le->le_flags, LF_REFILL_INPROGRESS);
		return;
	}

	/*
	 * See how many refill periods have passed since we last
	 * did a refill.
	 */
	period = le->_le.le_refill.le_refill_period;
	elapsed = now - le->_le.le_refill.le_last_refill;
	if ((period == 0) || (elapsed < period)) {
		flag_clear(&le->le_flags, LF_REFILL_INPROGRESS);
		return;
	}

	/*
	 * Optimize for the most common case of only one or two
	 * periods elapsing.
	 */
	periods = 0;
	while ((periods < 2) && (elapsed > 0)) {
		periods++;
		elapsed -= period;
	}

	/*
	 * OK, it's been a long time.  Do a divide to figure out
	 * how long.
	 */
	if (elapsed > 0)
		periods = (now - le->_le.le_refill.le_last_refill) / period;

	balance = le->le_credit - le->le_debit;
	due = periods * le->le_limit;

	if (balance - due < 0)
		due = balance;

	assertf(due >= 0,"now=%llu, ledger=%p, entry=%d, balance=%lld, due=%lld", now, ledger, entry, balance, due);

	OSAddAtomic64(due, &le->le_debit);

	assert(le->le_debit >= 0);

	/*
	 * If we've completely refilled the pool, set the refill time to now.
	 * Otherwise set it to the time at which it last should have been
	 * fully refilled.
	 */
	if (balance == due)
		le->_le.le_refill.le_last_refill = now;
	else
		le->_le.le_refill.le_last_refill += (le->_le.le_refill.le_refill_period * periods);

	flag_clear(&le->le_flags, LF_REFILL_INPROGRESS);

	lprintf(("Refill %lld %lld->%lld\n", periods, balance, balance - due));
	if (!limit_exceeded(le))
		ledger_limit_entry_wakeup(le);
}