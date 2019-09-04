#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ le_last_refill; scalar_t__ le_refill_period; } ;
struct TYPE_8__ {TYPE_1__ le_refill; } ;
struct ledger_entry {int le_flags; TYPE_2__ _le; } ;
struct ledger_callback {int /*<<< orphan*/  lc_param1; int /*<<< orphan*/  lc_param0; int /*<<< orphan*/  (* lc_func ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* ledger_t ;
struct TYPE_9__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LEDGER_ACTION_BLOCK ; 
 int LEDGER_ACTION_CALLBACK ; 
 scalar_t__ LEDGER_WARNING_DIPPED_BELOW ; 
 scalar_t__ LEDGER_WARNING_ROSE_ABOVE ; 
 int LF_CALLED_BACK ; 
 int LF_REFILL_SCHEDULED ; 
 int LF_TRACKING_MAX ; 
 int LF_WARNED ; 
 int /*<<< orphan*/  assert (int) ; 
 struct ledger_callback* entry_get_callback (TYPE_3__*,int) ; 
 int flag_clear (int*,int) ; 
 int flag_set (int*,int) ; 
 int /*<<< orphan*/  ledger_refill (scalar_t__,TYPE_3__*,int) ; 
 scalar_t__ limit_exceeded (struct ledger_entry*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_level_exceeded (struct ledger_entry*) ; 

__attribute__((used)) static uint32_t
ledger_check_needblock(ledger_t l, uint64_t now)
{
	int i;
	uint32_t flags, block = 0;
	struct ledger_entry *le;
	struct ledger_callback *lc;


	for (i = 0; i < l->l_size; i++) {
		le = &l->l_entries[i];

		lc = entry_get_callback(l, i);

		if (limit_exceeded(le) == FALSE) {
			if (le->le_flags & LEDGER_ACTION_CALLBACK) {
				/*
				 * If needed, invoke the callback as a warning.
				 * This needs to happen both when the balance rises above
				 * the warning level, and also when it dips back below it.
				 */
				assert(lc != NULL);
				/*
				 * See comments for matching logic in ledger_check_new_balance().
				 */
				if (warn_level_exceeded(le)) {
					flags = flag_set(&le->le_flags, LF_WARNED);
					if ((flags & LF_WARNED) == 0) {
						lc->lc_func(LEDGER_WARNING_ROSE_ABOVE, lc->lc_param0, lc->lc_param1);
					}
				} else {
					flags = flag_clear(&le->le_flags, LF_WARNED);
					if (flags & LF_WARNED) {
						lc->lc_func(LEDGER_WARNING_DIPPED_BELOW, lc->lc_param0, lc->lc_param1);
					}
				}
			}

			continue;
		}

		/* We're over the limit, so refill if we are eligible and past due. */
		if (le->le_flags & LF_REFILL_SCHEDULED) {
			assert(!(le->le_flags & LF_TRACKING_MAX));

			if ((le->_le.le_refill.le_last_refill + le->_le.le_refill.le_refill_period) > now) {
				ledger_refill(now, l, i);
				if (limit_exceeded(le) == FALSE)
					continue;
			}
		}

		if (le->le_flags & LEDGER_ACTION_BLOCK)
			block = 1;
		if ((le->le_flags & LEDGER_ACTION_CALLBACK) == 0)
			continue;

                /*
                 * If the LEDGER_ACTION_CALLBACK flag is on, we expect there to
                 * be a registered callback.
                 */
		assert(lc != NULL);
		flags = flag_set(&le->le_flags, LF_CALLED_BACK);
		/* Callback has already been called */
		if (flags & LF_CALLED_BACK)
			continue;
		lc->lc_func(FALSE, lc->lc_param0, lc->lc_param1);
	}
	return(block);
}