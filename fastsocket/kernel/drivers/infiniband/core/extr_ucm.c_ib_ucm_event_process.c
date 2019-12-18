#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  port; int /*<<< orphan*/  pkey; } ;
struct TYPE_28__ {int /*<<< orphan*/  status; } ;
struct TYPE_26__ {int /*<<< orphan*/  path; } ;
struct TYPE_24__ {int /*<<< orphan*/  reason; } ;
struct TYPE_22__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_17__ {int /*<<< orphan*/  send_status; int /*<<< orphan*/  sidr_rep_resp; TYPE_9__ sidr_req_resp; TYPE_7__ apr_resp; TYPE_5__ lap_resp; TYPE_3__ rej_resp; TYPE_1__ mra_resp; int /*<<< orphan*/  rep_resp; int /*<<< orphan*/  req_resp; } ;
struct TYPE_19__ {int /*<<< orphan*/  present; TYPE_11__ u; } ;
struct ib_ucm_event {void* data; TYPE_13__ resp; void* info; scalar_t__ info_len; scalar_t__ data_len; } ;
struct TYPE_20__ {void* info; scalar_t__ info_len; } ;
struct TYPE_16__ {int /*<<< orphan*/  port; int /*<<< orphan*/  pkey; } ;
struct TYPE_29__ {void* apr_info; scalar_t__ info_len; int /*<<< orphan*/  ap_status; } ;
struct TYPE_27__ {int /*<<< orphan*/  alternate_path; } ;
struct TYPE_25__ {void* ari; scalar_t__ ari_length; int /*<<< orphan*/  reason; } ;
struct TYPE_23__ {int /*<<< orphan*/  service_timeout; } ;
struct TYPE_21__ {int /*<<< orphan*/  alternate_path; } ;
struct TYPE_18__ {int /*<<< orphan*/  send_status; TYPE_14__ sidr_rep_rcvd; TYPE_10__ sidr_req_rcvd; TYPE_8__ apr_rcvd; TYPE_6__ lap_rcvd; TYPE_4__ rej_rcvd; TYPE_2__ mra_rcvd; int /*<<< orphan*/  rep_rcvd; TYPE_15__ req_rcvd; } ;
struct ib_cm_event {int event; void* private_data; TYPE_12__ param; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_CM_APR_PRIVATE_DATA_SIZE ; 
#define  IB_CM_APR_RECEIVED 138 
 scalar_t__ IB_CM_DREP_PRIVATE_DATA_SIZE ; 
#define  IB_CM_DREP_RECEIVED 137 
 scalar_t__ IB_CM_DREQ_PRIVATE_DATA_SIZE ; 
#define  IB_CM_DREQ_RECEIVED 136 
 scalar_t__ IB_CM_LAP_PRIVATE_DATA_SIZE ; 
#define  IB_CM_LAP_RECEIVED 135 
 scalar_t__ IB_CM_MRA_PRIVATE_DATA_SIZE ; 
#define  IB_CM_MRA_RECEIVED 134 
 scalar_t__ IB_CM_REJ_PRIVATE_DATA_SIZE ; 
#define  IB_CM_REJ_RECEIVED 133 
 scalar_t__ IB_CM_REP_PRIVATE_DATA_SIZE ; 
#define  IB_CM_REP_RECEIVED 132 
 scalar_t__ IB_CM_REQ_PRIVATE_DATA_SIZE ; 
#define  IB_CM_REQ_RECEIVED 131 
 scalar_t__ IB_CM_RTU_PRIVATE_DATA_SIZE ; 
#define  IB_CM_RTU_RECEIVED 130 
 scalar_t__ IB_CM_SIDR_REP_PRIVATE_DATA_SIZE ; 
#define  IB_CM_SIDR_REP_RECEIVED 129 
 scalar_t__ IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE ; 
#define  IB_CM_SIDR_REQ_RECEIVED 128 
 int /*<<< orphan*/  IB_UCM_PRES_ALTERNATE ; 
 int /*<<< orphan*/  IB_UCM_PRES_DATA ; 
 int /*<<< orphan*/  IB_UCM_PRES_INFO ; 
 int /*<<< orphan*/  IB_UCM_PRES_PRIMARY ; 
 int /*<<< orphan*/  ib_copy_path_rec_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_ucm_event_rep_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_ucm_event_req_get (int /*<<< orphan*/ *,TYPE_15__*) ; 
 int /*<<< orphan*/  ib_ucm_event_sidr_rep_get (int /*<<< orphan*/ *,TYPE_14__*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_ucm_event_process(struct ib_cm_event *evt,
				struct ib_ucm_event *uvt)
{
	void *info = NULL;

	switch (evt->event) {
	case IB_CM_REQ_RECEIVED:
		ib_ucm_event_req_get(&uvt->resp.u.req_resp,
				     &evt->param.req_rcvd);
		uvt->data_len      = IB_CM_REQ_PRIVATE_DATA_SIZE;
		uvt->resp.present  = IB_UCM_PRES_PRIMARY;
		uvt->resp.present |= (evt->param.req_rcvd.alternate_path ?
				      IB_UCM_PRES_ALTERNATE : 0);
		break;
	case IB_CM_REP_RECEIVED:
		ib_ucm_event_rep_get(&uvt->resp.u.rep_resp,
				     &evt->param.rep_rcvd);
		uvt->data_len = IB_CM_REP_PRIVATE_DATA_SIZE;
		break;
	case IB_CM_RTU_RECEIVED:
		uvt->data_len = IB_CM_RTU_PRIVATE_DATA_SIZE;
		uvt->resp.u.send_status = evt->param.send_status;
		break;
	case IB_CM_DREQ_RECEIVED:
		uvt->data_len = IB_CM_DREQ_PRIVATE_DATA_SIZE;
		uvt->resp.u.send_status = evt->param.send_status;
		break;
	case IB_CM_DREP_RECEIVED:
		uvt->data_len = IB_CM_DREP_PRIVATE_DATA_SIZE;
		uvt->resp.u.send_status = evt->param.send_status;
		break;
	case IB_CM_MRA_RECEIVED:
		uvt->resp.u.mra_resp.timeout =
					evt->param.mra_rcvd.service_timeout;
		uvt->data_len = IB_CM_MRA_PRIVATE_DATA_SIZE;
		break;
	case IB_CM_REJ_RECEIVED:
		uvt->resp.u.rej_resp.reason = evt->param.rej_rcvd.reason;
		uvt->data_len = IB_CM_REJ_PRIVATE_DATA_SIZE;
		uvt->info_len = evt->param.rej_rcvd.ari_length;
		info	      = evt->param.rej_rcvd.ari;
		break;
	case IB_CM_LAP_RECEIVED:
		ib_copy_path_rec_to_user(&uvt->resp.u.lap_resp.path,
					 evt->param.lap_rcvd.alternate_path);
		uvt->data_len = IB_CM_LAP_PRIVATE_DATA_SIZE;
		uvt->resp.present = IB_UCM_PRES_ALTERNATE;
		break;
	case IB_CM_APR_RECEIVED:
		uvt->resp.u.apr_resp.status = evt->param.apr_rcvd.ap_status;
		uvt->data_len = IB_CM_APR_PRIVATE_DATA_SIZE;
		uvt->info_len = evt->param.apr_rcvd.info_len;
		info	      = evt->param.apr_rcvd.apr_info;
		break;
	case IB_CM_SIDR_REQ_RECEIVED:
		uvt->resp.u.sidr_req_resp.pkey =
					evt->param.sidr_req_rcvd.pkey;
		uvt->resp.u.sidr_req_resp.port =
					evt->param.sidr_req_rcvd.port;
		uvt->data_len = IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE;
		break;
	case IB_CM_SIDR_REP_RECEIVED:
		ib_ucm_event_sidr_rep_get(&uvt->resp.u.sidr_rep_resp,
					  &evt->param.sidr_rep_rcvd);
		uvt->data_len = IB_CM_SIDR_REP_PRIVATE_DATA_SIZE;
		uvt->info_len = evt->param.sidr_rep_rcvd.info_len;
		info	      = evt->param.sidr_rep_rcvd.info;
		break;
	default:
		uvt->resp.u.send_status = evt->param.send_status;
		break;
	}

	if (uvt->data_len) {
		uvt->data = kmemdup(evt->private_data, uvt->data_len, GFP_KERNEL);
		if (!uvt->data)
			goto err1;

		uvt->resp.present |= IB_UCM_PRES_DATA;
	}

	if (uvt->info_len) {
		uvt->info = kmemdup(info, uvt->info_len, GFP_KERNEL);
		if (!uvt->info)
			goto err2;

		uvt->resp.present |= IB_UCM_PRES_INFO;
	}
	return 0;

err2:
	kfree(uvt->data);
err1:
	return -ENOMEM;
}