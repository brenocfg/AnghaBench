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
struct controller {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*) ; 
 scalar_t__ is_ctrl_busy (struct controller*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int shpc_poll_ctrl_busy (struct controller*) ; 
 scalar_t__ shpchp_poll_mode ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static inline int shpc_wait_cmd(struct controller *ctrl)
{
	int retval = 0;
	unsigned long timeout = msecs_to_jiffies(1000);
	int rc;

	if (shpchp_poll_mode)
		rc = shpc_poll_ctrl_busy(ctrl);
	else
		rc = wait_event_interruptible_timeout(ctrl->queue,
						!is_ctrl_busy(ctrl), timeout);
	if (!rc && is_ctrl_busy(ctrl)) {
		retval = -EIO;
		ctrl_err(ctrl, "Command not completed in 1000 msec\n");
	} else if (rc < 0) {
		retval = -EINTR;
		ctrl_info(ctrl, "Command was interrupted by a signal\n");
	}

	return retval;
}