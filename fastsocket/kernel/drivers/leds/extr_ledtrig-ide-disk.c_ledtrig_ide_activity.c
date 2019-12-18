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

/* Variables and functions */
 int /*<<< orphan*/  ide_activity ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ledtrig_ide_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void ledtrig_ide_activity(void)
{
	ide_activity++;
	if (!timer_pending(&ledtrig_ide_timer))
		mod_timer(&ledtrig_ide_timer, jiffies + msecs_to_jiffies(10));
}