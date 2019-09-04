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
 int /*<<< orphan*/ * dtrace_provider ; 

int
dtrace_attached(void)
{
	/*
	 * dtrace_provider will be non-NULL iff the DTrace driver has
	 * attached.  (It's non-NULL because DTrace is always itself a
	 * provider.)
	 */
	return (dtrace_provider != NULL);
}