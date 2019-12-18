#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  dev; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_devdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APM_CRITICAL_SUSPEND ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SHARPSL_APM_QUEUED ; 
 int /*<<< orphan*/  SHARPSL_STATUS_FATAL ; 
 int /*<<< orphan*/  SHARPSL_STATUS_LOCK ; 
 int /*<<< orphan*/  apm_queue_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sharpsl_fatal_isr(int irq, void *dev_id)
{
	int is_fatal = 0;

	if (!sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_LOCK)) {
		dev_err(sharpsl_pm.dev, "Battery now Unlocked! Suspending.\n");
		is_fatal = 1;
	}

	if (!sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_FATAL)) {
		dev_err(sharpsl_pm.dev, "Fatal Batt Error! Suspending.\n");
		is_fatal = 1;
	}

	if (!(sharpsl_pm.flags & SHARPSL_APM_QUEUED) && is_fatal) {
		sharpsl_pm.flags |= SHARPSL_APM_QUEUED;
		apm_queue_event(APM_CRITICAL_SUSPEND);
	}

	return IRQ_HANDLED;
}