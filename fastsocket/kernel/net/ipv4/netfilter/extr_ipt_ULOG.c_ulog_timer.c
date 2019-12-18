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
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulog_lock ; 
 int /*<<< orphan*/  ulog_send (unsigned long) ; 

__attribute__((used)) static void ulog_timer(unsigned long data)
{
	pr_debug("ipt_ULOG: timer function called, calling ulog_send\n");

	/* lock to protect against somebody modifying our structure
	 * from ipt_ulog_target at the same time */
	spin_lock_bh(&ulog_lock);
	ulog_send(data);
	spin_unlock_bh(&ulog_lock);
}