#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union fsf_status_qual {int /*<<< orphan*/ * word; } ;
struct zfcp_unit {TYPE_3__* port; } ;
struct zfcp_fsf_req {int status; TYPE_2__* qtcb; struct zfcp_unit* data; } ;
struct TYPE_8__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_6__ {int fsf_status; union fsf_status_qual fsf_status_qual; } ;
struct TYPE_7__ {TYPE_1__ header; } ;

/* Variables and functions */
#define  FSF_ADAPTER_STATUS_AVAILABLE 136 
#define  FSF_FCP_COMMAND_DOES_NOT_EXIST 135 
#define  FSF_GOOD 134 
#define  FSF_LUN_BOXED 133 
#define  FSF_LUN_HANDLE_NOT_VALID 132 
#define  FSF_PORT_BOXED 131 
#define  FSF_PORT_HANDLE_NOT_VALID 130 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 129 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 128 
 int ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED ; 
 int ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_port_boxed (TYPE_3__*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_port_reopen (TYPE_3__*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_unit_boxed (struct zfcp_unit*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fc_test_link (TYPE_3__*) ; 

__attribute__((used)) static void zfcp_fsf_abort_fcp_command_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_unit *unit = req->data;
	union fsf_status_qual *fsq = &req->qtcb->header.fsf_status_qual;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		return;

	switch (req->qtcb->header.fsf_status) {
	case FSF_PORT_HANDLE_NOT_VALID:
		if (fsq->word[0] == fsq->word[1]) {
			zfcp_erp_adapter_reopen(unit->port->adapter, 0,
						"fsafch1", req);
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		}
		break;
	case FSF_LUN_HANDLE_NOT_VALID:
		if (fsq->word[0] == fsq->word[1]) {
			zfcp_erp_port_reopen(unit->port, 0, "fsafch2", req);
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		}
		break;
	case FSF_FCP_COMMAND_DOES_NOT_EXIST:
		req->status |= ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED;
		break;
	case FSF_PORT_BOXED:
		zfcp_erp_port_boxed(unit->port, "fsafch3", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_LUN_BOXED:
		zfcp_erp_unit_boxed(unit, "fsafch4", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
                break;
	case FSF_ADAPTER_STATUS_AVAILABLE:
		switch (fsq->word[0]) {
		case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(unit->port);
			/* fall through */
		case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
		}
		break;
	case FSF_GOOD:
		req->status |= ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED;
		break;
	}
}