#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zfcp_port {scalar_t__ wwpn; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  status; TYPE_4__* adapter; TYPE_2__* qtcb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * halfword; } ;
struct fsf_qtcb_header {TYPE_1__ fsf_status_qual; } ;
struct TYPE_8__ {TYPE_3__* ccw_device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct fsf_qtcb_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  zfcp_act_eval_err (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_port_access_denied (struct zfcp_port*,char*,struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_access_denied_port(struct zfcp_fsf_req *req,
					struct zfcp_port *port)
{
	struct fsf_qtcb_header *header = &req->qtcb->header;
	dev_warn(&req->adapter->ccw_device->dev,
		 "Access denied to port 0x%016Lx\n",
		 (unsigned long long)port->wwpn);
	zfcp_act_eval_err(req->adapter, header->fsf_status_qual.halfword[0]);
	zfcp_act_eval_err(req->adapter, header->fsf_status_qual.halfword[1]);
	zfcp_erp_port_access_denied(port, "fspad_1", req);
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
}