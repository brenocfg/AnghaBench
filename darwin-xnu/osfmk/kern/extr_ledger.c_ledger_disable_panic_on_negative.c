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
struct ledger_entry {int /*<<< orphan*/  le_flags; } ;
typedef  TYPE_1__* ledger_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_VALID (TYPE_1__*,int) ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LF_PANIC_ON_NEGATIVE ; 
 int /*<<< orphan*/  flag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
ledger_disable_panic_on_negative(ledger_t ledger, int entry)
{
	struct ledger_entry *le;

	if (!ENTRY_VALID(ledger, entry))
		return (KERN_INVALID_ARGUMENT);

	le = &ledger->l_entries[entry];

	flag_clear(&le->le_flags, LF_PANIC_ON_NEGATIVE);

	return (KERN_SUCCESS);
}