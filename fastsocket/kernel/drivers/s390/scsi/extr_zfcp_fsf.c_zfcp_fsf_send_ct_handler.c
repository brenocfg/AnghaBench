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
struct zfcp_send_ct {int /*<<< orphan*/  handler_data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; } ;
struct zfcp_fsf_req {int status; TYPE_1__* qtcb; struct zfcp_send_ct* data; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * word; } ;
struct fsf_qtcb_header {int fsf_status; TYPE_2__ fsf_status_qual; } ;
struct TYPE_3__ {struct fsf_qtcb_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  FSF_ACCESS_DENIED 140 
#define  FSF_ADAPTER_STATUS_AVAILABLE 139 
#define  FSF_GENERIC_COMMAND_REJECTED 138 
#define  FSF_GOOD 137 
#define  FSF_PAYLOAD_SIZE_MISMATCH 136 
#define  FSF_PORT_BOXED 135 
#define  FSF_PORT_HANDLE_NOT_VALID 134 
#define  FSF_REQUEST_SIZE_TOO_LARGE 133 
#define  FSF_RESPONSE_SIZE_TOO_LARGE 132 
#define  FSF_SBAL_MISMATCH 131 
#define  FSF_SERVICE_CLASS_NOT_SUPPORTED 130 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 129 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 128 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_san_ct_response (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_class_not_supp (struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_send_ct_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct zfcp_send_ct *send_ct = req->data;
	struct fsf_qtcb_header *header = &req->qtcb->header;

	send_ct->status = -EINVAL;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		goto skip_fsfstatus;

	switch (header->fsf_status) {
        case FSF_GOOD:
		zfcp_dbf_san_ct_response(req);
		send_ct->status = 0;
		break;
        case FSF_SERVICE_CLASS_NOT_SUPPORTED:
		zfcp_fsf_class_not_supp(req);
		break;
        case FSF_ADAPTER_STATUS_AVAILABLE:
                switch (header->fsf_status_qual.word[0]){
                case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
                case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
                }
                break;
	case FSF_ACCESS_DENIED:
		break;
        case FSF_PORT_BOXED:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reopen(adapter, 0, "fsscth1", req);
		/* fall through */
	case FSF_GENERIC_COMMAND_REJECTED:
	case FSF_PAYLOAD_SIZE_MISMATCH:
	case FSF_REQUEST_SIZE_TOO_LARGE:
	case FSF_RESPONSE_SIZE_TOO_LARGE:
	case FSF_SBAL_MISMATCH:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	}

skip_fsfstatus:
	if (send_ct->handler)
		send_ct->handler(send_ct->handler_data);
}