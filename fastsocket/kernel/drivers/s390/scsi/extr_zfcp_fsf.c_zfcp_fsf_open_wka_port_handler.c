#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_wka_port {int /*<<< orphan*/  completion_wq; void* status; int /*<<< orphan*/  handle; int /*<<< orphan*/  d_id; } ;
struct zfcp_fsf_req {int status; TYPE_3__* adapter; TYPE_1__* qtcb; struct zfcp_wka_port* data; } ;
struct fsf_qtcb_header {int fsf_status; int /*<<< orphan*/  port_handle; } ;
struct TYPE_6__ {TYPE_2__* ccw_device; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct fsf_qtcb_header header; } ;

/* Variables and functions */
#define  FSF_ACCESS_DENIED 132 
#define  FSF_ADAPTER_STATUS_AVAILABLE 131 
#define  FSF_GOOD 130 
#define  FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED 129 
#define  FSF_PORT_ALREADY_OPEN 128 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 void* ZFCP_WKA_PORT_OFFLINE ; 
 void* ZFCP_WKA_PORT_ONLINE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_fsf_open_wka_port_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_wka_port *wka_port = req->data;
	struct fsf_qtcb_header *header = &req->qtcb->header;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR) {
		wka_port->status = ZFCP_WKA_PORT_OFFLINE;
		goto out;
	}

	switch (header->fsf_status) {
	case FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "Opening WKA port 0x%x failed\n", wka_port->d_id);
		/* fall through */
	case FSF_ADAPTER_STATUS_AVAILABLE:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		/* fall through */
	case FSF_ACCESS_DENIED:
		wka_port->status = ZFCP_WKA_PORT_OFFLINE;
		break;
	case FSF_GOOD:
		wka_port->handle = header->port_handle;
		/* fall through */
	case FSF_PORT_ALREADY_OPEN:
		wka_port->status = ZFCP_WKA_PORT_ONLINE;
	}
out:
	wake_up(&wka_port->completion_wq);
}