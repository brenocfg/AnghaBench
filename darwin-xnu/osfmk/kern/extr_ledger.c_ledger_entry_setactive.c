#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ledger_entry {int le_flags; } ;
typedef  TYPE_1__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int LF_ENTRY_ACTIVE ; 
 int /*<<< orphan*/  flag_set (int*,int) ; 

kern_return_t
ledger_entry_setactive(ledger_t ledger, int entry)
{
	struct ledger_entry *le;

	if ((ledger == NULL)  || (entry < 0) || (entry >= ledger->l_size))
		return (KERN_INVALID_ARGUMENT);

	le = &ledger->l_entries[entry];
	if ((le->le_flags & LF_ENTRY_ACTIVE) == 0) {
		flag_set(&le->le_flags, LF_ENTRY_ACTIVE);
	}
	return (KERN_SUCCESS);
}