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
struct TYPE_2__ {int netfn; int data_len; int* data; } ;
struct ipmi_recv_msg {int* msg_data; TYPE_1__ msg; int /*<<< orphan*/  recv_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_RESPONSE_RECV_TYPE ; 
 int /*<<< orphan*/  deliver_response (struct ipmi_recv_msg*) ; 

__attribute__((used)) static void
deliver_err_response(struct ipmi_recv_msg *msg, int err)
{
	msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	msg->msg_data[0] = err;
	msg->msg.netfn |= 1; /* Convert to a response. */
	msg->msg.data_len = 1;
	msg->msg.data = msg->msg_data;
	deliver_response(msg);
}