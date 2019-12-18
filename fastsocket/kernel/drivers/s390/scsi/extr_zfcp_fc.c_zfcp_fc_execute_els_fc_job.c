#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct zfcp_port {int d_id; } ;
struct TYPE_15__ {int d_id; unsigned long handler_data; int /*<<< orphan*/  handler; int /*<<< orphan*/  resp; int /*<<< orphan*/  req; struct zfcp_adapter* adapter; } ;
struct zfcp_els_fc_job {TYPE_7__ els; struct fc_bsg_job* job; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct fc_rport {int /*<<< orphan*/  port_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  sg_list; } ;
struct TYPE_12__ {int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {TYPE_6__* req; TYPE_5__ reply_payload; TYPE_4__ request_payload; TYPE_3__* request; struct Scsi_Host* shost; struct fc_rport* rport; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_16__ {int /*<<< orphan*/  config_lock; } ;
struct TYPE_14__ {int timeout; } ;
struct TYPE_9__ {int* port_id; } ;
struct TYPE_10__ {TYPE_1__ h_els; } ;
struct TYPE_11__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zfcp_els_fc_job*) ; 
 struct zfcp_els_fc_job* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 TYPE_8__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_fc_generic_els_handler ; 
 int zfcp_fsf_send_els (TYPE_7__*,int) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 

int zfcp_fc_execute_els_fc_job(struct fc_bsg_job *job)
{
	struct zfcp_els_fc_job *els_fc_job;
	struct fc_rport *rport = job->rport;
	struct Scsi_Host *shost;
	struct zfcp_adapter *adapter;
	struct zfcp_port *port;
	u8 *port_did;

	shost = rport ? rport_to_shost(rport) : job->shost;
	adapter = (struct zfcp_adapter *)shost->hostdata[0];

	if (!(atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_OPEN))
		return -EINVAL;

	els_fc_job = kzalloc(sizeof(struct zfcp_els_fc_job), GFP_KERNEL);
	if (!els_fc_job)
		return -ENOMEM;

	els_fc_job->els.adapter = adapter;
	if (rport) {
		read_lock_irq(&zfcp_data.config_lock);
		port = zfcp_get_port_by_wwpn(adapter, rport->port_name);
		if (port)
			els_fc_job->els.d_id = port->d_id;
		read_unlock_irq(&zfcp_data.config_lock);
		if (!port) {
			kfree(els_fc_job);
			return -EINVAL;
		}
	} else {
		port_did = job->request->rqst_data.h_els.port_id;
		els_fc_job->els.d_id = (port_did[0] << 16) +
					(port_did[1] << 8) + port_did[2];
	}

	els_fc_job->els.req = job->request_payload.sg_list;
	els_fc_job->els.resp = job->reply_payload.sg_list;
	els_fc_job->els.handler = zfcp_fc_generic_els_handler;
	els_fc_job->els.handler_data = (unsigned long) els_fc_job;
	els_fc_job->job = job;

	return zfcp_fsf_send_els(&els_fc_job->els, job->req->timeout / HZ);
}