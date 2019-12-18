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
 int /*<<< orphan*/  SMBIOD_DATA_READY ; 
 scalar_t__ SMBIOD_DEAD ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smbiod_flags ; 
 scalar_t__ smbiod_state ; 
 int /*<<< orphan*/  smbiod_wait ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void smbiod_wake_up(void)
{
	if (smbiod_state == SMBIOD_DEAD)
		return;
	set_bit(SMBIOD_DATA_READY, &smbiod_flags);
	wake_up_interruptible(&smbiod_wait);
}