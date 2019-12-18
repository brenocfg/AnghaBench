#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct ledger_entry_info {void* lei_last_refill; void* lei_refill_period; scalar_t__ lei_debit; scalar_t__ lei_credit; scalar_t__ lei_balance; int /*<<< orphan*/  lei_limit; } ;
struct TYPE_3__ {scalar_t__ le_last_refill; scalar_t__ le_refill_period; } ;
struct TYPE_4__ {TYPE_1__ le_refill; } ;
struct ledger_entry {int le_flags; TYPE_2__ _le; scalar_t__ le_debit; scalar_t__ le_credit; int /*<<< orphan*/  le_limit; } ;

/* Variables and functions */
 int LF_REFILL_SCHEDULED ; 
 void* abstime_to_nsecs (scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ledger_entry_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ledger_fill_entry_info(struct ledger_entry      *le,
                       struct ledger_entry_info *lei,
                       uint64_t                  now)
{
	assert(le  != NULL);
	assert(lei != NULL);

	memset(lei, 0, sizeof (*lei));

	lei->lei_limit         = le->le_limit;
	lei->lei_credit        = le->le_credit;
	lei->lei_debit         = le->le_debit;
	lei->lei_balance       = lei->lei_credit - lei->lei_debit;
	lei->lei_refill_period = (le->le_flags & LF_REFILL_SCHEDULED) ? 
							     abstime_to_nsecs(le->_le.le_refill.le_refill_period) : 0;
	lei->lei_last_refill   = abstime_to_nsecs(now - le->_le.le_refill.le_last_refill);
}