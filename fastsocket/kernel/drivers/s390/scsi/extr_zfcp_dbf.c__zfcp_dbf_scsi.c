#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct zfcp_fsf_req {int /*<<< orphan*/  issued; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  req_id; TYPE_4__* qtcb; } ;
struct zfcp_dbf_scsi_record {unsigned long scsi_cmnd; int rsp_validity; int sns_info_len; unsigned long old_fsf_reqid; int /*<<< orphan*/  fsf_issued; int /*<<< orphan*/  fsf_seqno; int /*<<< orphan*/  fsf_reqid; int /*<<< orphan*/  sns_info; int /*<<< orphan*/  rsp_code; int /*<<< orphan*/  rsp_resid; int /*<<< orphan*/  rsp_scsi_status; int /*<<< orphan*/  scsi_allowed; int /*<<< orphan*/  scsi_retries; int /*<<< orphan*/  scsi_opcode; int /*<<< orphan*/  scsi_serial; int /*<<< orphan*/  scsi_result; int /*<<< orphan*/  scsi_lun; int /*<<< orphan*/  scsi_id; int /*<<< orphan*/  tag2; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf_dump {int total_size; int offset; int size; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  scsi_lock; int /*<<< orphan*/  scsi; struct zfcp_dbf_scsi_record scsi_buf; } ;
struct scsi_cmnd {char* cmnd; int /*<<< orphan*/  allowed; int /*<<< orphan*/  retries; scalar_t__ cmd_len; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  result; TYPE_1__* device; } ;
struct TYPE_12__ {int fr_sns_len; int /*<<< orphan*/  fr_resid; } ;
struct TYPE_11__ {int fr_flags; int /*<<< orphan*/  fr_status; } ;
struct fcp_resp_with_ext {TYPE_6__ ext; TYPE_5__ resp; } ;
struct fcp_resp_rsp_info {int /*<<< orphan*/  rsp_code; } ;
struct TYPE_8__ {int /*<<< orphan*/  fcp_rsp; } ;
struct TYPE_9__ {TYPE_2__ io; } ;
struct TYPE_10__ {TYPE_3__ bottom; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int FCP_RSP_LEN_VAL ; 
 int FCP_SNS_LEN_VAL ; 
 int ZFCP_DBF_SCSI_FCP_SNS_INFO ; 
 scalar_t__ ZFCP_DBF_SCSI_MAX_FCP_SNS_INFO ; 
 int ZFCP_DBF_SCSI_OPCODE ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_scsi_record*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_scsi_record*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void _zfcp_dbf_scsi(const char *tag, const char *tag2, int level,
		    struct zfcp_dbf *dbf, struct scsi_cmnd *scsi_cmnd,
		    struct zfcp_fsf_req *fsf_req, unsigned long old_req_id)
{
	struct zfcp_dbf_scsi_record *rec = &dbf->scsi_buf;
	struct zfcp_dbf_dump *dump = (struct zfcp_dbf_dump *)rec;
	unsigned long flags;
	struct fcp_resp_with_ext *fcp_rsp;
	struct fcp_resp_rsp_info *fcp_rsp_info = NULL;
	char *fcp_sns_info = NULL;
	int offset = 0, buflen = 0;

	spin_lock_irqsave(&dbf->scsi_lock, flags);
	do {
		memset(rec, 0, sizeof(*rec));
		if (offset == 0) {
			strncpy(rec->tag, tag, ZFCP_DBF_TAG_SIZE);
			strncpy(rec->tag2, tag2, ZFCP_DBF_TAG_SIZE);
			if (scsi_cmnd != NULL) {
				if (scsi_cmnd->device) {
					rec->scsi_id = scsi_cmnd->device->id;
					rec->scsi_lun = scsi_cmnd->device->lun;
				}
				rec->scsi_result = scsi_cmnd->result;
				rec->scsi_cmnd = (unsigned long)scsi_cmnd;
				rec->scsi_serial = scsi_cmnd->serial_number;
				memcpy(rec->scsi_opcode, scsi_cmnd->cmnd,
					min((int)scsi_cmnd->cmd_len,
						ZFCP_DBF_SCSI_OPCODE));
				rec->scsi_retries = scsi_cmnd->retries;
				rec->scsi_allowed = scsi_cmnd->allowed;
			}
			if (fsf_req != NULL) {
				fcp_rsp = (struct fcp_resp_with_ext *)
					&(fsf_req->qtcb->bottom.io.fcp_rsp);
				fcp_rsp_info = (struct fcp_resp_rsp_info *)
					&fcp_rsp[1];
				fcp_sns_info = (char *) &fcp_rsp[1];
				if (fcp_rsp->resp.fr_flags & FCP_RSP_LEN_VAL)
					fcp_sns_info += fcp_rsp->ext.fr_sns_len;

				rec->rsp_validity = fcp_rsp->resp.fr_flags;
				rec->rsp_scsi_status = fcp_rsp->resp.fr_status;
				rec->rsp_resid = fcp_rsp->ext.fr_resid;
				if (fcp_rsp->resp.fr_flags & FCP_RSP_LEN_VAL)
					rec->rsp_code = fcp_rsp_info->rsp_code;
				if (fcp_rsp->resp.fr_flags & FCP_SNS_LEN_VAL) {
					buflen = min(fcp_rsp->ext.fr_sns_len,
					   (u32)ZFCP_DBF_SCSI_MAX_FCP_SNS_INFO);
					rec->sns_info_len = buflen;
					memcpy(rec->sns_info, fcp_sns_info,
					       min(buflen,
						   ZFCP_DBF_SCSI_FCP_SNS_INFO));
					offset += min(buflen,
						      ZFCP_DBF_SCSI_FCP_SNS_INFO);
				}

				rec->fsf_reqid = fsf_req->req_id;
				rec->fsf_seqno = fsf_req->seq_no;
				rec->fsf_issued = fsf_req->issued;
			}
			rec->old_fsf_reqid = old_req_id;
		} else {
			strncpy(dump->tag, "dump", ZFCP_DBF_TAG_SIZE);
			dump->total_size = buflen;
			dump->offset = offset;
			dump->size = min(buflen - offset,
					 (int)sizeof(struct
						     zfcp_dbf_scsi_record) -
					 (int)sizeof(struct zfcp_dbf_dump));
			memcpy(dump->data, fcp_sns_info + offset, dump->size);
			offset += dump->size;
		}
		debug_event(dbf->scsi, level, rec, sizeof(*rec));
	} while (offset < buflen);
	spin_unlock_irqrestore(&dbf->scsi_lock, flags);
}