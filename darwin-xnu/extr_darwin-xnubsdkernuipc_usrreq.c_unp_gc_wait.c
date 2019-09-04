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
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uipc_lock ; 
 scalar_t__ unp_gcing ; 
 scalar_t__ unp_gcthread ; 
 int unp_gcwait ; 

void
unp_gc_wait(void)
{
	if (unp_gcthread == current_thread())
		return;

	while (unp_gcing != 0) {
		unp_gcwait = 1;
		msleep(&unp_gcing, uipc_lock, 0 , "unp_gc_wait", NULL);
	}
}