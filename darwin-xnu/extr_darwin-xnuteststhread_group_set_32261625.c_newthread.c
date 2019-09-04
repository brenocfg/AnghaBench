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
 int /*<<< orphan*/  TEST_EVENTID ; 
 int /*<<< orphan*/  kdebug_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void*
newthread(void *arg)
{
#pragma unused(arg)
	while (1) {
		kdebug_trace(TEST_EVENTID, 0, 0, 0, 0);
		sleep(1);
	}
}