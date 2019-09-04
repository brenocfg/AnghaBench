#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ledger_template_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int lt_cnt; TYPE_1__* lt_entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  et_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LF_PANIC_ON_NEGATIVE ; 
 int /*<<< orphan*/  template_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  template_unlock (TYPE_2__*) ; 

kern_return_t
ledger_panic_on_negative(ledger_template_t template, int entry)
{
	template_lock(template);

	if ((entry < 0) || (entry >= template->lt_cnt)) {
		template_unlock(template);
		return (KERN_INVALID_VALUE);
	}

	template->lt_entries[entry].et_flags |= LF_PANIC_ON_NEGATIVE;

	template_unlock(template);

	return (KERN_SUCCESS);
}