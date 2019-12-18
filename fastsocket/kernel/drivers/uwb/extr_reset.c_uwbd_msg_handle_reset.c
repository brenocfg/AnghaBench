#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {int (* reset ) (struct uwb_rc*) ;TYPE_1__ uwb_dev; } ;
struct uwb_event {struct uwb_rc* rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_reset_all (struct uwb_rc*) ; 

int uwbd_msg_handle_reset(struct uwb_event *evt)
{
	struct uwb_rc *rc = evt->rc;
	int ret;

	dev_info(&rc->uwb_dev.dev, "resetting radio controller\n");
	ret = rc->reset(rc);
	if (ret < 0) {
		dev_err(&rc->uwb_dev.dev, "failed to reset hardware: %d\n", ret);
		goto error;
	}
	return 0;
error:
	/* Nothing can be done except try the reset again. Wait a bit
	   to avoid reset loops during probe() or remove(). */
	msleep(1000);
	uwb_rc_reset_all(rc);
	return ret;
}