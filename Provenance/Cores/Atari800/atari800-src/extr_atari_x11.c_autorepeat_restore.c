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
 int /*<<< orphan*/  XAutoRepeatOff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XAutoRepeatOn (int /*<<< orphan*/ ) ; 
 scalar_t__ autorepeat ; 
 int /*<<< orphan*/  display ; 

__attribute__((used)) static void autorepeat_restore(void)
{
	if (autorepeat)
		XAutoRepeatOn(display);
	else
		XAutoRepeatOff(display);
}