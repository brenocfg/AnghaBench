#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zfcp_unit {int /*<<< orphan*/  status; TYPE_4__* port; } ;
struct zfcp_fsf_req {int status; TYPE_3__* qtcb; struct zfcp_unit* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_7__ {int /*<<< orphan*/ * word; } ;
struct TYPE_8__ {int fsf_status; TYPE_1__ fsf_status_qual; } ;
struct TYPE_9__ {TYPE_2__ header; } ;

/* Variables and functions */
#define  FSF_ADAPTER_STATUS_AVAILABLE 134 
#define  FSF_GOOD 133 
#define  FSF_LUN_HANDLE_NOT_VALID 132 
#define  FSF_PORT_BOXED 131 
#define  FSF_PORT_HANDLE_NOT_VALID 130 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 129 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 128 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  atomic_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_port_boxed (TYPE_4__*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_port_reopen (TYPE_4__*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fc_test_link (TYPE_4__*) ; 

__attribute__((used)) static void zfcp_fsf_close_unit_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_unit *unit = req->data;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		return;

	switch (req->qtcb->header.fsf_status) {
	case FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reopen(unit->port->adapter, 0, "fscuh_1", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_LUN_HANDLE_NOT_VALID:
		zfcp_erp_port_reopen(unit->port, 0, "fscuh_2", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_PORT_BOXED:
		zfcp_erp_port_boxed(unit->port, "fscuh_3", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_ADAPTER_STATUS_AVAILABLE:
		switch (req->qtcb->header.fsf_status_qual.word[0]) {
		case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(unit->port);
			/* fall through */
		case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
		}
		break;
	case FSF_GOOD:
		atomic_clear_mask(ZFCP_STATUS_COMMON_OPEN, &unit->status);
		break;
	}
}