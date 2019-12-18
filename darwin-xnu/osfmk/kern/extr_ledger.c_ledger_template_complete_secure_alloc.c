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
struct ledger_entry {int dummy; } ;
struct ledger {int dummy; } ;
typedef  TYPE_1__* ledger_template_t ;
struct TYPE_3__ {int lt_cnt; int lt_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_ledger_alloc_init (size_t) ; 

void
ledger_template_complete_secure_alloc(ledger_template_t template)
{
	size_t ledger_size;
	ledger_size = sizeof(struct ledger) + (template->lt_cnt * sizeof(struct ledger_entry));
	pmap_ledger_alloc_init(ledger_size);
	template->lt_initialized = true;
}