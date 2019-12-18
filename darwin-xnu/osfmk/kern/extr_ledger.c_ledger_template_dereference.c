#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ledger_template_t ;
struct TYPE_6__ {scalar_t__ lt_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  template_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_1__*) ; 

void
ledger_template_dereference(ledger_template_t template)
{
	template_lock(template);
	template->lt_refs--;
	template_unlock(template);

	if (template->lt_refs == 0)
		kfree(template, sizeof (*template));
}