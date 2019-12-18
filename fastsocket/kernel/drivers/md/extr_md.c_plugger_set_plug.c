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
struct plug_handle {int /*<<< orphan*/  unplug_timer; int /*<<< orphan*/  unplug_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLUGGED_FLAG ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void plugger_set_plug(struct plug_handle *plug)
{
	if (!test_and_set_bit(PLUGGED_FLAG, &plug->unplug_flag))
		mod_timer(&plug->unplug_timer, jiffies + msecs_to_jiffies(3)+1);
}