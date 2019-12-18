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
 scalar_t__ disable_poll ; 
 int /*<<< orphan*/  via ; 
 int /*<<< orphan*/  via_pmu_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
pmu_poll(void)
{
	if (!via)
		return;
	if (disable_poll)
		return;
	via_pmu_interrupt(0, NULL);
}