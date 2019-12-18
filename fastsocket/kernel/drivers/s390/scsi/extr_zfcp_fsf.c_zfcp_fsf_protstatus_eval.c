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
union fsf_prot_status_qual {int /*<<< orphan*/  link_down_info; int /*<<< orphan*/ * word; } ;
struct zfcp_fsf_req {int status; struct fsf_qtcb* qtcb; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {TYPE_3__* ccw_device; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int prot_status; union fsf_prot_status_qual prot_status_qual; } ;
struct TYPE_5__ {scalar_t__ req_handle; } ;
struct TYPE_6__ {TYPE_1__ support; } ;
struct fsf_qtcb {TYPE_4__ prefix; TYPE_2__ bottom; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  FSF_PROT_DUPLICATE_REQUEST_ID 137 
#define  FSF_PROT_ERROR_STATE 136 
#define  FSF_PROT_FSF_STATUS_PRESENTED 135 
#define  FSF_PROT_GOOD 134 
#define  FSF_PROT_HOST_CONNECTION_INITIALIZING 133 
#define  FSF_PROT_LINK_DOWN 132 
#define  FSF_PROT_QTCB_VERSION_ERROR 131 
#define  FSF_PROT_REEST_QUEUE 130 
#define  FSF_PROT_SEQ_NUMB_ERROR 129 
#define  FSF_PROT_UNSUPP_QTCB_TYPE 128 
 int /*<<< orphan*/  FSF_QTCB_CURRENT_VERSION ; 
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_HOST_CON_INIT ; 
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_FSFREQ_DISMISSED ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_fsf_response (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_modify_adapter_status (struct zfcp_adapter*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_link_down_info_eval (struct zfcp_fsf_req*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_siosl (struct zfcp_adapter*) ; 

__attribute__((used)) static void zfcp_fsf_protstatus_eval(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct fsf_qtcb *qtcb = req->qtcb;
	union fsf_prot_status_qual *psq = &qtcb->prefix.prot_status_qual;

	zfcp_dbf_hba_fsf_response(req);

	if (req->status & ZFCP_STATUS_FSFREQ_DISMISSED) {
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		return;
	}

	switch (qtcb->prefix.prot_status) {
	case FSF_PROT_GOOD:
	case FSF_PROT_FSF_STATUS_PRESENTED:
		return;
	case FSF_PROT_QTCB_VERSION_ERROR:
		dev_err(&adapter->ccw_device->dev,
			"QTCB version 0x%x not supported by FCP adapter "
			"(0x%x to 0x%x)\n", FSF_QTCB_CURRENT_VERSION,
			psq->word[0], psq->word[1]);
		zfcp_erp_adapter_shutdown(adapter, 0, "fspse_1", req);
		break;
	case FSF_PROT_ERROR_STATE:
	case FSF_PROT_SEQ_NUMB_ERROR:
		zfcp_erp_adapter_reopen(adapter, 0, "fspse_2", req);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_PROT_UNSUPP_QTCB_TYPE:
		dev_err(&adapter->ccw_device->dev,
			"The QTCB type is not supported by the FCP adapter\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "fspse_3", req);
		break;
	case FSF_PROT_HOST_CONNECTION_INITIALIZING:
		atomic_set_mask(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
				&adapter->status);
		break;
	case FSF_PROT_DUPLICATE_REQUEST_ID:
		dev_err(&adapter->ccw_device->dev,
			"0x%Lx is an ambiguous request identifier\n",
			(unsigned long long)qtcb->bottom.support.req_handle);
		zfcp_erp_adapter_shutdown(adapter, 0, "fspse_4", req);
		break;
	case FSF_PROT_LINK_DOWN:
		zfcp_fsf_link_down_info_eval(req, "fspse_5",
					     &psq->link_down_info);
		/* FIXME: reopening adapter now? better wait for link up */
		zfcp_erp_adapter_reopen(adapter, 0, "fspse_6", req);
		break;
	case FSF_PROT_REEST_QUEUE:
		/* All ports should be marked as ready to run again */
		zfcp_erp_modify_adapter_status(adapter, "fspse_7", NULL,
					       ZFCP_STATUS_COMMON_RUNNING,
					       ZFCP_SET);
		zfcp_erp_adapter_reopen(adapter,
					ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED |
					ZFCP_STATUS_COMMON_ERP_FAILED,
					"fspse_8", req);
		break;
	default:
		dev_err(&adapter->ccw_device->dev,
			"0x%x is not a valid transfer protocol status\n",
			qtcb->prefix.prot_status);
		zfcp_qdio_siosl(adapter);
		zfcp_erp_adapter_shutdown(adapter, 0, "fspse_9", req);
	}
	req->status |= ZFCP_STATUS_FSFREQ_ERROR;
}