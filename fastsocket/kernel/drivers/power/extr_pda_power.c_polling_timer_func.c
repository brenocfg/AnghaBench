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
struct TYPE_2__ {int /*<<< orphan*/  polling_interval; } ;

/* Variables and functions */
 scalar_t__ PDA_PSY_TO_CHANGE ; 
 int /*<<< orphan*/  ac_irq ; 
 scalar_t__ ac_status ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ new_ac_status ; 
 scalar_t__ new_usb_status ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  polling_timer ; 
 int /*<<< orphan*/  psy_changed () ; 
 int /*<<< orphan*/  update_status () ; 
 int /*<<< orphan*/  usb_irq ; 
 scalar_t__ usb_status ; 

__attribute__((used)) static void polling_timer_func(unsigned long unused)
{
	int changed = 0;

	dev_dbg(dev, "polling...\n");

	update_status();

	if (!ac_irq && new_ac_status != ac_status) {
		ac_status = PDA_PSY_TO_CHANGE;
		changed = 1;
	}

	if (!usb_irq && new_usb_status != usb_status) {
		usb_status = PDA_PSY_TO_CHANGE;
		changed = 1;
	}

	if (changed)
		psy_changed();

	mod_timer(&polling_timer,
		  jiffies + msecs_to_jiffies(pdata->polling_interval));
}