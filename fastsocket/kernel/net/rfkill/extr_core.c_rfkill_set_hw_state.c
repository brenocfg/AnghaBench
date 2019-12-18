#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rfkill {int /*<<< orphan*/  uevent_work; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int __rfkill_set_hw_state (struct rfkill*,int,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

bool rfkill_set_hw_state(struct rfkill *rfkill, bool blocked)
{
	bool ret, change;

	ret = __rfkill_set_hw_state(rfkill, blocked, &change);

	if (!rfkill->registered)
		return ret;

	if (change)
		schedule_work(&rfkill->uevent_work);

	return ret;
}