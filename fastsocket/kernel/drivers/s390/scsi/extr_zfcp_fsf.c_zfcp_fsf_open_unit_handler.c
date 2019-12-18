#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zfcp_unit {TYPE_5__* port; scalar_t__ fcp_lun; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; } ;
struct zfcp_fsf_req {int status; TYPE_2__* qtcb; struct zfcp_unit* data; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int connection_features; int adapter_features; TYPE_4__* ccw_device; } ;
struct fsf_queue_designator {int /*<<< orphan*/  hla; int /*<<< orphan*/  cssid; } ;
struct TYPE_9__ {int /*<<< orphan*/ * word; struct fsf_queue_designator fsf_queue_designator; } ;
struct fsf_qtcb_header {int fsf_status; int /*<<< orphan*/  lun_handle; TYPE_3__ fsf_status_qual; } ;
struct fsf_qtcb_bottom_support {int lun_access_info; } ;
struct TYPE_11__ {scalar_t__ wwpn; int /*<<< orphan*/  adapter; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct fsf_qtcb_bottom_support support; } ;
struct TYPE_8__ {TYPE_1__ bottom; struct fsf_qtcb_header header; } ;

/* Variables and functions */
#define  FSF_ACCESS_DENIED 138 
#define  FSF_ADAPTER_STATUS_AVAILABLE 137 
 int FSF_FEATURE_LUN_SHARING ; 
 int FSF_FEATURE_NPIV_MODE ; 
#define  FSF_GOOD 136 
#define  FSF_INVALID_COMMAND_OPTION 135 
#define  FSF_LUN_ALREADY_OPEN 134 
#define  FSF_LUN_SHARING_VIOLATION 133 
#define  FSF_MAXIMUM_NUMBER_OF_LUNS_EXCEEDED 132 
#define  FSF_PORT_BOXED 131 
#define  FSF_PORT_HANDLE_NOT_VALID 130 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 129 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 128 
 int FSF_UNIT_ACCESS_EXCLUSIVE ; 
 int FSF_UNIT_ACCESS_OUTBOUND_TRANSFER ; 
 int ZFCP_STATUS_COMMON_ACCESS_BOXED ; 
 int ZFCP_STATUS_COMMON_ACCESS_DENIED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int ZFCP_STATUS_UNIT_READONLY ; 
 int ZFCP_STATUS_UNIT_SHARED ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_mask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  zfcp_act_eval_err (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_ccw_priv_sch (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_port_boxed (TYPE_5__*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_unit_access_denied (struct zfcp_unit*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_unit_failed (struct zfcp_unit*,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_unit_shutdown (struct zfcp_unit*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fc_test_link (TYPE_5__*) ; 
 int /*<<< orphan*/  zfcp_fsf_access_denied_unit (struct zfcp_fsf_req*,struct zfcp_unit*) ; 

__attribute__((used)) static void zfcp_fsf_open_unit_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct zfcp_unit *unit = req->data;
	struct fsf_qtcb_header *header = &req->qtcb->header;
	struct fsf_qtcb_bottom_support *bottom = &req->qtcb->bottom.support;
	struct fsf_queue_designator *queue_designator =
				&header->fsf_status_qual.fsf_queue_designator;
	int exclusive, readwrite;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		return;

	atomic_clear_mask(ZFCP_STATUS_COMMON_ACCESS_DENIED |
			  ZFCP_STATUS_COMMON_ACCESS_BOXED |
			  ZFCP_STATUS_UNIT_SHARED |
			  ZFCP_STATUS_UNIT_READONLY,
			  &unit->status);

	switch (header->fsf_status) {

	case FSF_PORT_HANDLE_NOT_VALID:
		zfcp_erp_adapter_reopen(unit->port->adapter, 0, "fsouh_1", req);
		/* fall through */
	case FSF_LUN_ALREADY_OPEN:
		break;
	case FSF_ACCESS_DENIED:
		zfcp_fsf_access_denied_unit(req, unit);
		atomic_clear_mask(ZFCP_STATUS_UNIT_SHARED, &unit->status);
		atomic_clear_mask(ZFCP_STATUS_UNIT_READONLY, &unit->status);
		break;
	case FSF_PORT_BOXED:
		zfcp_erp_port_boxed(unit->port, "fsouh_2", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_LUN_SHARING_VIOLATION:
		if (header->fsf_status_qual.word[0])
			dev_warn(&adapter->ccw_device->dev,
				 "LUN 0x%Lx on port 0x%Lx is already in "
				 "use by CSS%d, MIF Image ID %x\n",
				 (unsigned long long)unit->fcp_lun,
				 (unsigned long long)unit->port->wwpn,
				 queue_designator->cssid,
				 queue_designator->hla);
		else
			zfcp_act_eval_err(adapter,
					  header->fsf_status_qual.word[2]);
		zfcp_erp_unit_access_denied(unit, "fsouh_3", req);
		atomic_clear_mask(ZFCP_STATUS_UNIT_SHARED, &unit->status);
		atomic_clear_mask(ZFCP_STATUS_UNIT_READONLY, &unit->status);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_MAXIMUM_NUMBER_OF_LUNS_EXCEEDED:
		dev_warn(&adapter->ccw_device->dev,
			 "No handle is available for LUN "
			 "0x%016Lx on port 0x%016Lx\n",
			 (unsigned long long)unit->fcp_lun,
			 (unsigned long long)unit->port->wwpn);
		zfcp_erp_unit_failed(unit, "fsouh_4", req);
		/* fall through */
	case FSF_INVALID_COMMAND_OPTION:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_ADAPTER_STATUS_AVAILABLE:
		switch (header->fsf_status_qual.word[0]) {
		case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			zfcp_fc_test_link(unit->port);
			/* fall through */
		case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
		}
		break;

	case FSF_GOOD:
		unit->handle = header->lun_handle;
		atomic_set_mask(ZFCP_STATUS_COMMON_OPEN, &unit->status);

		if (!(adapter->connection_features & FSF_FEATURE_NPIV_MODE) &&
		    (adapter->adapter_features & FSF_FEATURE_LUN_SHARING) &&
		    !zfcp_ccw_priv_sch(adapter)) {
			exclusive = (bottom->lun_access_info &
					FSF_UNIT_ACCESS_EXCLUSIVE);
			readwrite = (bottom->lun_access_info &
					FSF_UNIT_ACCESS_OUTBOUND_TRANSFER);

			if (!exclusive)
		                atomic_set_mask(ZFCP_STATUS_UNIT_SHARED,
						&unit->status);

			if (!readwrite) {
                		atomic_set_mask(ZFCP_STATUS_UNIT_READONLY,
						&unit->status);
				dev_info(&adapter->ccw_device->dev,
					 "SCSI device at LUN 0x%016Lx on port "
					 "0x%016Lx opened read-only\n",
					 (unsigned long long)unit->fcp_lun,
					 (unsigned long long)unit->port->wwpn);
        		}

        		if (exclusive && !readwrite) {
				dev_err(&adapter->ccw_device->dev,
					"Exclusive read-only access not "
					"supported (unit 0x%016Lx, "
					"port 0x%016Lx)\n",
					(unsigned long long)unit->fcp_lun,
					(unsigned long long)unit->port->wwpn);
				zfcp_erp_unit_failed(unit, "fsouh_5", req);
				req->status |= ZFCP_STATUS_FSFREQ_ERROR;
				zfcp_erp_unit_shutdown(unit, 0, "fsouh_6", req);
        		} else if (!exclusive && readwrite) {
				dev_err(&adapter->ccw_device->dev,
					"Shared read-write access not "
					"supported (unit 0x%016Lx, port "
					"0x%016Lx)\n",
					(unsigned long long)unit->fcp_lun,
					(unsigned long long)unit->port->wwpn);
				zfcp_erp_unit_failed(unit, "fsouh_7", req);
				req->status |= ZFCP_STATUS_FSFREQ_ERROR;
				zfcp_erp_unit_shutdown(unit, 0, "fsouh_8", req);
        		}
		}
		break;
	}
}