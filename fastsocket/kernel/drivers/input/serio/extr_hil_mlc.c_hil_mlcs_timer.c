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
 scalar_t__ HZ ; 
 int /*<<< orphan*/  hil_mlcs_kicker ; 
 int hil_mlcs_probe ; 
 int /*<<< orphan*/  hil_mlcs_tasklet ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hil_mlcs_timer(unsigned long data)
{
	hil_mlcs_probe = 1;
	tasklet_schedule(&hil_mlcs_tasklet);
	/* Re-insert the periodic task. */
	if (!timer_pending(&hil_mlcs_kicker))
		mod_timer(&hil_mlcs_kicker, jiffies + HZ);
}