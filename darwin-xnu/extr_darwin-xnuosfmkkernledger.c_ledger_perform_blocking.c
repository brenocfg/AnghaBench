#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ le_refill_period; scalar_t__ le_last_refill; } ;
struct TYPE_6__ {TYPE_1__ le_refill; } ;
struct ledger_entry {int le_flags; TYPE_2__ _le; } ;
typedef  TYPE_3__* ledger_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_7__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_LEDGER ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int LEDGER_ACTION_BLOCK ; 
 int LF_TRACKING_MAX ; 
 int /*<<< orphan*/  LF_WAKE_NEEDED ; 
 scalar_t__ THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ THREAD_WAITING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait_deadline (struct ledger_entry*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  flag_set (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  limit_exceeded (struct ledger_entry*) ; 
 scalar_t__ thread_block_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
ledger_perform_blocking(ledger_t l)
{
	int i;
	kern_return_t ret;
	struct ledger_entry *le;

	for (i = 0; i < l->l_size; i++) {
		le = &l->l_entries[i];
		if ((!limit_exceeded(le)) ||
		    ((le->le_flags & LEDGER_ACTION_BLOCK) == 0))
			continue;

		assert(!(le->le_flags & LF_TRACKING_MAX));

		/* Prepare to sleep until the resource is refilled */
		ret = assert_wait_deadline(le, THREAD_INTERRUPTIBLE,
		    le->_le.le_refill.le_last_refill + le->_le.le_refill.le_refill_period);
		if (ret != THREAD_WAITING)
			return(KERN_SUCCESS);

		/* Mark that somebody is waiting on this entry  */
		flag_set(&le->le_flags, LF_WAKE_NEEDED);

		ret = thread_block_reason(THREAD_CONTINUE_NULL, NULL,
		    AST_LEDGER);
		if (ret != THREAD_AWAKENED)
			return(KERN_SUCCESS);

		/*
		 * The world may have changed while we were asleep.
		 * Some other resource we need may have gone into
		 * deficit.  Or maybe we're supposed to die now.
		 * Go back to the top and reevaluate.
		 */
		return(KERN_FAILURE);
	}
	return(KERN_SUCCESS);
}