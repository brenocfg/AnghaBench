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
struct xsd_sockmsg {scalar_t__ type; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  transaction_mutex; int /*<<< orphan*/  request_mutex; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 scalar_t__ XS_ERROR ; 
 scalar_t__ XS_TRANSACTION_END ; 
 scalar_t__ XS_TRANSACTION_START ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* read_reply (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int xb_write (struct xsd_sockmsg*,scalar_t__) ; 
 TYPE_1__ xs_state ; 

void *xenbus_dev_request_and_reply(struct xsd_sockmsg *msg)
{
	void *ret;
	struct xsd_sockmsg req_msg = *msg;
	int err;

	if (req_msg.type == XS_TRANSACTION_START)
		down_read(&xs_state.transaction_mutex);

	mutex_lock(&xs_state.request_mutex);

	err = xb_write(msg, sizeof(*msg) + msg->len);
	if (err) {
		msg->type = XS_ERROR;
		ret = ERR_PTR(err);
	} else
		ret = read_reply(&msg->type, &msg->len);

	mutex_unlock(&xs_state.request_mutex);

	if ((msg->type == XS_TRANSACTION_END) ||
	    ((req_msg.type == XS_TRANSACTION_START) &&
	     (msg->type == XS_ERROR)))
		up_read(&xs_state.transaction_mutex);

	return ret;
}