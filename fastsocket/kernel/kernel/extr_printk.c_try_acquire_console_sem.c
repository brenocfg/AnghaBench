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
 int console_locked ; 
 scalar_t__ console_may_schedule ; 
 int /*<<< orphan*/  console_sem ; 
 scalar_t__ console_suspended ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int try_acquire_console_sem(void)
{
	if (down_trylock(&console_sem))
		return -1;
	if (console_suspended) {
		up(&console_sem);
		return -1;
	}
	console_locked = 1;
	console_may_schedule = 0;
	return 0;
}