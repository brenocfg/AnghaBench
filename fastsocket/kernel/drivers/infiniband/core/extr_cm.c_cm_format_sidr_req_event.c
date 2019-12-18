#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_sidr_req_event_param {int /*<<< orphan*/  port; struct ib_cm_id* listen_id; int /*<<< orphan*/  pkey; } ;
struct ib_cm_id {int dummy; } ;
struct TYPE_6__ {struct ib_cm_sidr_req_event_param sidr_req_rcvd; } ;
struct TYPE_8__ {int /*<<< orphan*/ * private_data; TYPE_1__ param; } ;
struct cm_work {TYPE_3__ cm_event; TYPE_2__* port; TYPE_5__* mad_recv_wc; } ;
struct cm_sidr_req_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  pkey; } ;
struct TYPE_9__ {scalar_t__ mad; } ;
struct TYPE_10__ {TYPE_4__ recv_buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  __be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm_format_sidr_req_event(struct cm_work *work,
				     struct ib_cm_id *listen_id)
{
	struct cm_sidr_req_msg *sidr_req_msg;
	struct ib_cm_sidr_req_event_param *param;

	sidr_req_msg = (struct cm_sidr_req_msg *)
				work->mad_recv_wc->recv_buf.mad;
	param = &work->cm_event.param.sidr_req_rcvd;
	param->pkey = __be16_to_cpu(sidr_req_msg->pkey);
	param->listen_id = listen_id;
	param->port = work->port->port_num;
	work->cm_event.private_data = &sidr_req_msg->private_data;
}