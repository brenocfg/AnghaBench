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
typedef  TYPE_2__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {TYPE_1__* l_entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  le_flags; int /*<<< orphan*/  le_warn_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_VALID (TYPE_2__*,int) ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LEDGER_ACTION_CALLBACK ; 
 int /*<<< orphan*/  LEDGER_LIMIT_INFINITY ; 
 int /*<<< orphan*/  flag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
ledger_disable_callback(ledger_t ledger, int entry)
{
	if (!ENTRY_VALID(ledger, entry))
		return (KERN_INVALID_VALUE);

	/*
	 * le_warn_level is used to indicate *if* this ledger has a warning configured,
	 * in addition to what that warning level is set to.
	 * This means a side-effect of ledger_disable_callback() is that the
	 * warning level is forgotten.
	 */
	ledger->l_entries[entry].le_warn_level = LEDGER_LIMIT_INFINITY;
	flag_clear(&ledger->l_entries[entry].le_flags, LEDGER_ACTION_CALLBACK);
	return (KERN_SUCCESS);
}