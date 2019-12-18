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
struct firedtv {int avc_reply_received; int /*<<< orphan*/  device; int /*<<< orphan*/  avc_wait; int /*<<< orphan*/  avc_data_length; int /*<<< orphan*/  avc_data; TYPE_1__* backend; } ;
struct TYPE_2__ {int (* write ) (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FCP_COMMAND_REGISTER ; 
 int /*<<< orphan*/  avc_debug ; 
 int /*<<< orphan*/  debug_fcp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int stub1 (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avc_write(struct firedtv *fdtv)
{
	int err, retry;

	fdtv->avc_reply_received = false;

	for (retry = 0; retry < 6; retry++) {
		if (unlikely(avc_debug))
			debug_fcp(fdtv->avc_data, fdtv->avc_data_length);

		err = fdtv->backend->write(fdtv, FCP_COMMAND_REGISTER,
				fdtv->avc_data, fdtv->avc_data_length);
		if (err) {
			dev_err(fdtv->device, "FCP command write failed\n");

			return err;
		}

		/*
		 * AV/C specs say that answers should be sent within 150 ms.
		 * Time out after 200 ms.
		 */
		if (wait_event_timeout(fdtv->avc_wait,
				       fdtv->avc_reply_received,
				       msecs_to_jiffies(200)) != 0)
			return 0;
	}
	dev_err(fdtv->device, "FCP response timed out\n");

	return -ETIMEDOUT;
}