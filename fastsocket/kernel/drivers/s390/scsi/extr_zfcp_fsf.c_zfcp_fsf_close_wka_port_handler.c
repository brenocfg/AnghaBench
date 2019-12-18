#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zfcp_wka_port {int /*<<< orphan*/  completion_wq; int /*<<< orphan*/  status; int /*<<< orphan*/  adapter; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  status; TYPE_2__* qtcb; struct zfcp_wka_port* data; } ;
struct TYPE_3__ {scalar_t__ fsf_status; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ FSF_PORT_HANDLE_NOT_VALID ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  ZFCP_WKA_PORT_OFFLINE ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_close_wka_port_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_wka_port *wka_port = req->data;

	if (req->qtcb->header.fsf_status == FSF_PORT_HANDLE_NOT_VALID) {
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		zfcp_erp_adapter_reopen(wka_port->adapter, 0, "fscwph1", req);
	}

	wka_port->status = ZFCP_WKA_PORT_OFFLINE;
	wake_up(&wka_port->completion_wq);
}