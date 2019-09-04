#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * ledger_template_t ;
struct TYPE_2__ {int cpu_time; int energy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bank_ledger_template ; 
 TYPE_1__ bank_ledgers ; 
 int ledger_entry_add (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  ledger_template_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ledger_template_create (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
init_bank_ledgers(void) {
	ledger_template_t t;
	int idx;
	
	assert(bank_ledger_template == NULL);

	if ((t = ledger_template_create("Bank ledger")) == NULL)
		panic("couldn't create bank ledger template");

	if ((idx = ledger_entry_add(t, "cpu_time", "sched", "ns")) < 0) {
		panic("couldn't create cpu_time entry for bank ledger template");
	}
	bank_ledgers.cpu_time = idx;

	if ((idx = ledger_entry_add(t, "energy", "power", "nj")) < 0) {
		panic("couldn't create energy entry for bank ledger template");
	}
	bank_ledgers.energy = idx;

	ledger_template_complete(t);
	bank_ledger_template = t;
}