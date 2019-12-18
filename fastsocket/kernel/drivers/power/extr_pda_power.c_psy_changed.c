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
struct TYPE_2__ {int /*<<< orphan*/  wait_for_charger; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  supply_timer ; 
 int /*<<< orphan*/  update_charger () ; 

__attribute__((used)) static void psy_changed(void)
{
	update_charger();

	/*
	 * Okay, charger set. Now wait a bit before notifying supplicants,
	 * charge power should stabilize.
	 */
	mod_timer(&supply_timer,
		  jiffies + msecs_to_jiffies(pdata->wait_for_charger));
}