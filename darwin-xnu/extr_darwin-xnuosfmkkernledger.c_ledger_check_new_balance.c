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
typedef  int /*<<< orphan*/  thread_t ;
struct ledger_entry {int dummy; } ;
typedef  TYPE_1__* ledger_t ;
struct TYPE_4__ {int l_size; struct ledger_entry* l_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ledger_entry_check_new_balance (int /*<<< orphan*/ ,TYPE_1__*,int,struct ledger_entry*) ; 

void
ledger_check_new_balance(thread_t thread, ledger_t ledger, int entry)
{
	struct ledger_entry *le;
	assert(entry > 0 && entry <= ledger->l_size);
	le = &ledger->l_entries[entry];
	ledger_entry_check_new_balance(thread, ledger, entry, le);
}