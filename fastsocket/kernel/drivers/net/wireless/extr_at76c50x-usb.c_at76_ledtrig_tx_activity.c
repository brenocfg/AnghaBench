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
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ledtrig_tx_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_activity ; 

__attribute__((used)) static void at76_ledtrig_tx_activity(void)
{
	tx_activity++;
	if (!timer_pending(&ledtrig_tx_timer))
		mod_timer(&ledtrig_tx_timer, jiffies + HZ / 4);
}