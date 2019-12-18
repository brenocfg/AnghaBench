#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  union fsf_status_qual {int dummy; } fsf_status_qual ;
typedef  union fsf_status_qual fsf_prot_status_qual ;
struct zfcp_unit {int /*<<< orphan*/  fcp_lun; struct zfcp_port* port; } ;
struct zfcp_send_els {int ls_code; } ;
struct zfcp_port {int /*<<< orphan*/  wwpn; int /*<<< orphan*/  d_id; } ;
struct TYPE_18__ {int /*<<< orphan*/  sbal_response; int /*<<< orphan*/  sbal_last; int /*<<< orphan*/  sbal_first; } ;
struct zfcp_fsf_req {int fsf_command; int status; scalar_t__ data; scalar_t__ erp_action; int /*<<< orphan*/ * pool; TYPE_3__ queue_req; int /*<<< orphan*/  issued; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  req_id; struct fsf_qtcb* qtcb; } ;
struct TYPE_13__ {int ls_code; int /*<<< orphan*/  d_id; } ;
struct TYPE_22__ {int /*<<< orphan*/  lun_handle; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  fcp_lun; int /*<<< orphan*/  wwpn; } ;
struct TYPE_21__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwpn; } ;
struct TYPE_19__ {unsigned long cmnd; int /*<<< orphan*/  data_dir; int /*<<< orphan*/  serial; } ;
struct TYPE_14__ {TYPE_10__ els; TYPE_7__ unit; TYPE_6__ port; TYPE_4__ fcp; } ;
struct zfcp_dbf_hba_record_response {int fsf_command; int fsf_req_status; unsigned long erp_action; TYPE_11__ u; int /*<<< orphan*/  pool; int /*<<< orphan*/  sbal_response; int /*<<< orphan*/  sbal_last; int /*<<< orphan*/  sbal_first; int /*<<< orphan*/  fsf_status_qual; int /*<<< orphan*/  fsf_prot_status_qual; int /*<<< orphan*/  fsf_status; int /*<<< orphan*/  fsf_prot_status; int /*<<< orphan*/  fsf_issued; int /*<<< orphan*/  fsf_seqno; int /*<<< orphan*/  fsf_reqid; } ;
struct TYPE_16__ {struct zfcp_dbf_hba_record_response response; } ;
struct zfcp_dbf_hba_record {int /*<<< orphan*/  tag2; int /*<<< orphan*/  tag; TYPE_1__ u; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; struct zfcp_dbf_hba_record hba_buf; } ;
struct scsi_cmnd {int /*<<< orphan*/  serial_number; } ;
struct TYPE_15__ {int log_start; int log_length; int /*<<< orphan*/  lun_handle; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  fsf_status; union fsf_status_qual fsf_status_qual; } ;
struct TYPE_23__ {int /*<<< orphan*/  d_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  data_direction; } ;
struct TYPE_24__ {TYPE_8__ support; TYPE_5__ io; } ;
struct TYPE_17__ {int /*<<< orphan*/  prot_status; union fsf_status_qual prot_status_qual; } ;
struct fsf_qtcb {TYPE_12__ header; TYPE_9__ bottom; TYPE_2__ prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSF_PROT_STATUS_QUAL_SIZE ; 
#define  FSF_QTCB_ABORT_FCP_CMND 140 
#define  FSF_QTCB_CLOSE_LUN 139 
#define  FSF_QTCB_CLOSE_PHYSICAL_PORT 138 
#define  FSF_QTCB_CLOSE_PORT 137 
#define  FSF_QTCB_DOWNLOAD_CONTROL_FILE 136 
#define  FSF_QTCB_EXCHANGE_CONFIG_DATA 135 
#define  FSF_QTCB_EXCHANGE_PORT_DATA 134 
#define  FSF_QTCB_FCP_CMND 133 
#define  FSF_QTCB_OPEN_LUN 132 
#define  FSF_QTCB_OPEN_PORT_WITH_DID 131 
#define  FSF_QTCB_SEND_ELS 130 
#define  FSF_QTCB_SEND_GENERIC 129 
#define  FSF_QTCB_UPLOAD_CONTROL_FILE 128 
 int /*<<< orphan*/  FSF_STATUS_QUALIFIER_SIZE ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_hba_record*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,union fsf_status_qual*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_hexdump (int /*<<< orphan*/ ,struct zfcp_dbf_hba_record*,int,int,char*,int) ; 

void _zfcp_dbf_hba_fsf_response(const char *tag2, int level,
				struct zfcp_fsf_req *fsf_req,
				struct zfcp_dbf *dbf)
{
	struct fsf_qtcb *qtcb = fsf_req->qtcb;
	union fsf_prot_status_qual *prot_status_qual =
					&qtcb->prefix.prot_status_qual;
	union fsf_status_qual *fsf_status_qual = &qtcb->header.fsf_status_qual;
	struct scsi_cmnd *scsi_cmnd;
	struct zfcp_port *port;
	struct zfcp_unit *unit;
	struct zfcp_send_els *send_els;
	struct zfcp_dbf_hba_record *rec = &dbf->hba_buf;
	struct zfcp_dbf_hba_record_response *response = &rec->u.response;
	unsigned long flags;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(rec, 0, sizeof(*rec));
	strncpy(rec->tag, "resp", ZFCP_DBF_TAG_SIZE);
	strncpy(rec->tag2, tag2, ZFCP_DBF_TAG_SIZE);

	response->fsf_command = fsf_req->fsf_command;
	response->fsf_reqid = fsf_req->req_id;
	response->fsf_seqno = fsf_req->seq_no;
	response->fsf_issued = fsf_req->issued;
	response->fsf_prot_status = qtcb->prefix.prot_status;
	response->fsf_status = qtcb->header.fsf_status;
	memcpy(response->fsf_prot_status_qual,
	       prot_status_qual, FSF_PROT_STATUS_QUAL_SIZE);
	memcpy(response->fsf_status_qual,
	       fsf_status_qual, FSF_STATUS_QUALIFIER_SIZE);
	response->fsf_req_status = fsf_req->status;
	response->sbal_first = fsf_req->queue_req.sbal_first;
	response->sbal_last = fsf_req->queue_req.sbal_last;
	response->sbal_response = fsf_req->queue_req.sbal_response;
	response->pool = fsf_req->pool != NULL;
	response->erp_action = (unsigned long)fsf_req->erp_action;

	switch (fsf_req->fsf_command) {
	case FSF_QTCB_FCP_CMND:
		if (fsf_req->status & ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT)
			break;
		scsi_cmnd = (struct scsi_cmnd *)fsf_req->data;
		if (scsi_cmnd) {
			response->u.fcp.cmnd = (unsigned long)scsi_cmnd;
			response->u.fcp.serial = scsi_cmnd->serial_number;
			response->u.fcp.data_dir =
				qtcb->bottom.io.data_direction;
		}
		break;

	case FSF_QTCB_OPEN_PORT_WITH_DID:
	case FSF_QTCB_CLOSE_PORT:
	case FSF_QTCB_CLOSE_PHYSICAL_PORT:
		port = (struct zfcp_port *)fsf_req->data;
		response->u.port.wwpn = port->wwpn;
		response->u.port.d_id = port->d_id;
		response->u.port.port_handle = qtcb->header.port_handle;
		break;

	case FSF_QTCB_OPEN_LUN:
	case FSF_QTCB_CLOSE_LUN:
		unit = (struct zfcp_unit *)fsf_req->data;
		port = unit->port;
		response->u.unit.wwpn = port->wwpn;
		response->u.unit.fcp_lun = unit->fcp_lun;
		response->u.unit.port_handle = qtcb->header.port_handle;
		response->u.unit.lun_handle = qtcb->header.lun_handle;
		break;

	case FSF_QTCB_SEND_ELS:
		send_els = (struct zfcp_send_els *)fsf_req->data;
		response->u.els.d_id = qtcb->bottom.support.d_id;
		response->u.els.ls_code = send_els->ls_code >> 24;
		break;

	case FSF_QTCB_ABORT_FCP_CMND:
	case FSF_QTCB_SEND_GENERIC:
	case FSF_QTCB_EXCHANGE_CONFIG_DATA:
	case FSF_QTCB_EXCHANGE_PORT_DATA:
	case FSF_QTCB_DOWNLOAD_CONTROL_FILE:
	case FSF_QTCB_UPLOAD_CONTROL_FILE:
		break;
	}

	debug_event(dbf->hba, level, rec, sizeof(*rec));

	/* have fcp channel microcode fixed to use as little as possible */
	if (fsf_req->fsf_command != FSF_QTCB_FCP_CMND) {
		/* adjust length skipping trailing zeros */
		char *buf = (char *)qtcb + qtcb->header.log_start;
		int len = qtcb->header.log_length;
		for (; len && !buf[len - 1]; len--);
		zfcp_dbf_hexdump(dbf->hba, rec, sizeof(*rec), level, buf,
				 len);
	}

	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}