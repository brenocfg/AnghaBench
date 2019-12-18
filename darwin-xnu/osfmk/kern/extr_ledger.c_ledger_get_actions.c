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
struct TYPE_5__ {int le_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_VALID (TYPE_2__*,int) ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int LEDGER_ACTION_MASK ; 
 int /*<<< orphan*/  lprintf (char*) ; 

kern_return_t
ledger_get_actions(ledger_t ledger, int entry, int *actions)
{
	if (!ENTRY_VALID(ledger, entry))
		return (KERN_INVALID_VALUE);

	*actions = ledger->l_entries[entry].le_flags & LEDGER_ACTION_MASK;
	lprintf(("ledger_get_actions: %#x\n", *actions));	
	return (KERN_SUCCESS);
}