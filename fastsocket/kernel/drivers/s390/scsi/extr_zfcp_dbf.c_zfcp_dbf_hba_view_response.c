#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int d_id; int ls_code; } ;
struct TYPE_8__ {int wwpn; int fcp_lun; int port_handle; int lun_handle; } ;
struct TYPE_7__ {int wwpn; int d_id; int port_handle; } ;
struct TYPE_6__ {int data_dir; int cmnd; int serial; } ;
struct TYPE_10__ {TYPE_4__ els; TYPE_3__ unit; TYPE_2__ port; TYPE_1__ fcp; } ;
struct zfcp_dbf_hba_record_response {int fsf_command; int fsf_reqid; int fsf_seqno; int fsf_prot_status; int fsf_status; int fsf_req_status; int sbal_first; int sbal_last; int sbal_response; int pool; TYPE_5__ u; int /*<<< orphan*/  fsf_status_qual; int /*<<< orphan*/  fsf_prot_status_qual; int /*<<< orphan*/  fsf_issued; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

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
 int ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  stck_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int,...) ; 
 int /*<<< orphan*/  zfcp_dbf_outd (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_dbf_hba_view_response(char **p,
				       struct zfcp_dbf_hba_record_response *r)
{
	struct timespec t;

	zfcp_dbf_out(p, "fsf_command", "0x%08x", r->fsf_command);
	zfcp_dbf_out(p, "fsf_reqid", "0x%0Lx", r->fsf_reqid);
	zfcp_dbf_out(p, "fsf_seqno", "0x%08x", r->fsf_seqno);
	stck_to_timespec(r->fsf_issued, &t);
	zfcp_dbf_out(p, "fsf_issued", "%011lu:%06lu", t.tv_sec, t.tv_nsec);
	zfcp_dbf_out(p, "fsf_prot_status", "0x%08x", r->fsf_prot_status);
	zfcp_dbf_out(p, "fsf_status", "0x%08x", r->fsf_status);
	zfcp_dbf_outd(p, "fsf_prot_status_qual", r->fsf_prot_status_qual,
		      FSF_PROT_STATUS_QUAL_SIZE, 0, FSF_PROT_STATUS_QUAL_SIZE);
	zfcp_dbf_outd(p, "fsf_status_qual", r->fsf_status_qual,
		      FSF_STATUS_QUALIFIER_SIZE, 0, FSF_STATUS_QUALIFIER_SIZE);
	zfcp_dbf_out(p, "fsf_req_status", "0x%08x", r->fsf_req_status);
	zfcp_dbf_out(p, "sbal_first", "0x%02x", r->sbal_first);
	zfcp_dbf_out(p, "sbal_last", "0x%02x", r->sbal_last);
	zfcp_dbf_out(p, "sbal_response", "0x%02x", r->sbal_response);
	zfcp_dbf_out(p, "pool", "0x%02x", r->pool);

	switch (r->fsf_command) {
	case FSF_QTCB_FCP_CMND:
		if (r->fsf_req_status & ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT)
			break;
		zfcp_dbf_out(p, "data_direction", "0x%04x", r->u.fcp.data_dir);
		zfcp_dbf_out(p, "scsi_cmnd", "0x%0Lx", r->u.fcp.cmnd);
		zfcp_dbf_out(p, "scsi_serial", "0x%016Lx", r->u.fcp.serial);
		p += sprintf(*p, "\n");
		break;

	case FSF_QTCB_OPEN_PORT_WITH_DID:
	case FSF_QTCB_CLOSE_PORT:
	case FSF_QTCB_CLOSE_PHYSICAL_PORT:
		zfcp_dbf_out(p, "wwpn", "0x%016Lx", r->u.port.wwpn);
		zfcp_dbf_out(p, "d_id", "0x%06x", r->u.port.d_id);
		zfcp_dbf_out(p, "port_handle", "0x%08x", r->u.port.port_handle);
		break;

	case FSF_QTCB_OPEN_LUN:
	case FSF_QTCB_CLOSE_LUN:
		zfcp_dbf_out(p, "wwpn", "0x%016Lx", r->u.unit.wwpn);
		zfcp_dbf_out(p, "fcp_lun", "0x%016Lx", r->u.unit.fcp_lun);
		zfcp_dbf_out(p, "port_handle", "0x%08x", r->u.unit.port_handle);
		zfcp_dbf_out(p, "lun_handle", "0x%08x", r->u.unit.lun_handle);
		break;

	case FSF_QTCB_SEND_ELS:
		zfcp_dbf_out(p, "d_id", "0x%06x", r->u.els.d_id);
		zfcp_dbf_out(p, "ls_code", "0x%02x", r->u.els.ls_code);
		break;

	case FSF_QTCB_ABORT_FCP_CMND:
	case FSF_QTCB_SEND_GENERIC:
	case FSF_QTCB_EXCHANGE_CONFIG_DATA:
	case FSF_QTCB_EXCHANGE_PORT_DATA:
	case FSF_QTCB_DOWNLOAD_CONTROL_FILE:
	case FSF_QTCB_UPLOAD_CONTROL_FILE:
		break;
	}
}