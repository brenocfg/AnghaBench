#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ib_sa_path_rec {int dummy; } ;
struct TYPE_9__ {TYPE_2__* mad; } ;
struct ib_mad_recv_wc {TYPE_3__ recv_buf; } ;
struct ib_mad_agent {struct cm_port* context; } ;
struct TYPE_11__ {int event; } ;
struct cm_work {int /*<<< orphan*/  work; struct cm_port* port; struct ib_mad_recv_wc* mad_recv_wc; TYPE_5__ cm_event; } ;
struct cm_req_msg {int /*<<< orphan*/  alt_local_lid; } ;
struct cm_port {TYPE_4__* counter_group; } ;
typedef  enum ib_cm_event_type { ____Placeholder_ib_cm_event_type } ib_cm_event_type ;
struct TYPE_12__ {int /*<<< orphan*/  wq; } ;
struct TYPE_10__ {int /*<<< orphan*/ * counter; } ;
struct TYPE_7__ {int attr_id; } ;
struct TYPE_8__ {TYPE_1__ mad_hdr; } ;

/* Variables and functions */
#define  CM_APR_ATTR_ID 138 
 size_t CM_ATTR_ID_OFFSET ; 
#define  CM_DREP_ATTR_ID 137 
#define  CM_DREQ_ATTR_ID 136 
#define  CM_LAP_ATTR_ID 135 
#define  CM_MRA_ATTR_ID 134 
 size_t CM_RECV ; 
#define  CM_REJ_ATTR_ID 133 
#define  CM_REP_ATTR_ID 132 
#define  CM_REQ_ATTR_ID 131 
#define  CM_RTU_ATTR_ID 130 
#define  CM_SIDR_REP_ATTR_ID 129 
#define  CM_SIDR_REQ_ATTR_ID 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_CM_APR_RECEIVED ; 
 int IB_CM_DREP_RECEIVED ; 
 int IB_CM_DREQ_RECEIVED ; 
 int IB_CM_LAP_RECEIVED ; 
 int IB_CM_MRA_RECEIVED ; 
 int IB_CM_REJ_RECEIVED ; 
 int IB_CM_REP_RECEIVED ; 
 int IB_CM_REQ_RECEIVED ; 
 int IB_CM_RTU_RECEIVED ; 
 int IB_CM_SIDR_REP_RECEIVED ; 
 int IB_CM_SIDR_REQ_RECEIVED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 size_t be16_to_cpu (int) ; 
 TYPE_6__ cm ; 
 int /*<<< orphan*/  cm_work_handler ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 struct cm_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm_recv_handler(struct ib_mad_agent *mad_agent,
			    struct ib_mad_recv_wc *mad_recv_wc)
{
	struct cm_port *port = mad_agent->context;
	struct cm_work *work;
	enum ib_cm_event_type event;
	u16 attr_id;
	int paths = 0;

	switch (mad_recv_wc->recv_buf.mad->mad_hdr.attr_id) {
	case CM_REQ_ATTR_ID:
		paths = 1 + (((struct cm_req_msg *) mad_recv_wc->recv_buf.mad)->
						    alt_local_lid != 0);
		event = IB_CM_REQ_RECEIVED;
		break;
	case CM_MRA_ATTR_ID:
		event = IB_CM_MRA_RECEIVED;
		break;
	case CM_REJ_ATTR_ID:
		event = IB_CM_REJ_RECEIVED;
		break;
	case CM_REP_ATTR_ID:
		event = IB_CM_REP_RECEIVED;
		break;
	case CM_RTU_ATTR_ID:
		event = IB_CM_RTU_RECEIVED;
		break;
	case CM_DREQ_ATTR_ID:
		event = IB_CM_DREQ_RECEIVED;
		break;
	case CM_DREP_ATTR_ID:
		event = IB_CM_DREP_RECEIVED;
		break;
	case CM_SIDR_REQ_ATTR_ID:
		event = IB_CM_SIDR_REQ_RECEIVED;
		break;
	case CM_SIDR_REP_ATTR_ID:
		event = IB_CM_SIDR_REP_RECEIVED;
		break;
	case CM_LAP_ATTR_ID:
		paths = 1;
		event = IB_CM_LAP_RECEIVED;
		break;
	case CM_APR_ATTR_ID:
		event = IB_CM_APR_RECEIVED;
		break;
	default:
		ib_free_recv_mad(mad_recv_wc);
		return;
	}

	attr_id = be16_to_cpu(mad_recv_wc->recv_buf.mad->mad_hdr.attr_id);
	atomic_long_inc(&port->counter_group[CM_RECV].
			counter[attr_id - CM_ATTR_ID_OFFSET]);

	work = kmalloc(sizeof *work + sizeof(struct ib_sa_path_rec) * paths,
		       GFP_KERNEL);
	if (!work) {
		ib_free_recv_mad(mad_recv_wc);
		return;
	}

	INIT_DELAYED_WORK(&work->work, cm_work_handler);
	work->cm_event.event = event;
	work->mad_recv_wc = mad_recv_wc;
	work->port = port;
	queue_delayed_work(cm.wq, &work->work, 0);
}