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
typedef  int /*<<< orphan*/  uint64_t ;
struct ledger_entry_info {int dummy; } ;
struct ledger_entry {int dummy; } ;
typedef  TYPE_1__* ledger_t ;
struct TYPE_3__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_fill_entry_info (struct ledger_entry*,struct ledger_entry_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

void
ledger_get_entry_info(ledger_t                  ledger,
                      int                       entry,
                      struct ledger_entry_info *lei)
{
	uint64_t now = mach_absolute_time();

	assert(ledger != NULL);
	assert(lei != NULL);

	if (entry >= 0 && entry < ledger->l_size) {
		struct ledger_entry *le = &ledger->l_entries[entry];
		ledger_fill_entry_info(le, lei, now);
	}
}