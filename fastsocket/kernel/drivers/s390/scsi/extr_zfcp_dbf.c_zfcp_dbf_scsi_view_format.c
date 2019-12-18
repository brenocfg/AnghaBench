#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct zfcp_dbf_scsi_record {scalar_t__ sns_info_len; int /*<<< orphan*/  sns_info; scalar_t__ rsp_code; scalar_t__ rsp_resid; scalar_t__ rsp_scsi_status; scalar_t__ rsp_validity; int /*<<< orphan*/  tag; int /*<<< orphan*/  fsf_issued; scalar_t__ fsf_seqno; scalar_t__ fsf_reqid; scalar_t__ old_fsf_reqid; scalar_t__ scsi_allowed; scalar_t__ scsi_retries; int /*<<< orphan*/  scsi_opcode; scalar_t__ scsi_serial; scalar_t__ scsi_cmnd; scalar_t__ scsi_result; scalar_t__ scsi_lun; scalar_t__ scsi_id; int /*<<< orphan*/  tag2; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_SCSI_FCP_SNS_INFO ; 
 scalar_t__ ZFCP_DBF_SCSI_OPCODE ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 scalar_t__ min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  stck_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  zfcp_dbf_outd (char**,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zfcp_dbf_tag (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_dbf_scsi_view_format(debug_info_t *id, struct debug_view *view,
				     char *out_buf, const char *in_buf)
{
	struct zfcp_dbf_scsi_record *r = (struct zfcp_dbf_scsi_record *)in_buf;
	struct timespec t;
	char *p = out_buf;

	if (strncmp(r->tag, "dump", ZFCP_DBF_TAG_SIZE) == 0)
		return 0;

	zfcp_dbf_tag(&p, "tag", r->tag);
	zfcp_dbf_tag(&p, "tag2", r->tag2);
	zfcp_dbf_out(&p, "scsi_id", "0x%08x", r->scsi_id);
	zfcp_dbf_out(&p, "scsi_lun", "0x%08x", r->scsi_lun);
	zfcp_dbf_out(&p, "scsi_result", "0x%08x", r->scsi_result);
	zfcp_dbf_out(&p, "scsi_cmnd", "0x%0Lx", r->scsi_cmnd);
	zfcp_dbf_out(&p, "scsi_serial", "0x%016Lx", r->scsi_serial);
	zfcp_dbf_outd(&p, "scsi_opcode", r->scsi_opcode, ZFCP_DBF_SCSI_OPCODE,
		      0, ZFCP_DBF_SCSI_OPCODE);
	zfcp_dbf_out(&p, "scsi_retries", "0x%02x", r->scsi_retries);
	zfcp_dbf_out(&p, "scsi_allowed", "0x%02x", r->scsi_allowed);
	if (strncmp(r->tag, "abrt", ZFCP_DBF_TAG_SIZE) == 0)
		zfcp_dbf_out(&p, "old_fsf_reqid", "0x%0Lx", r->old_fsf_reqid);
	zfcp_dbf_out(&p, "fsf_reqid", "0x%0Lx", r->fsf_reqid);
	zfcp_dbf_out(&p, "fsf_seqno", "0x%08x", r->fsf_seqno);
	stck_to_timespec(r->fsf_issued, &t);
	zfcp_dbf_out(&p, "fsf_issued", "%011lu:%06lu", t.tv_sec, t.tv_nsec);

	if (strncmp(r->tag, "rslt", ZFCP_DBF_TAG_SIZE) == 0) {
		zfcp_dbf_out(&p, "fcp_rsp_validity", "0x%02x", r->rsp_validity);
		zfcp_dbf_out(&p, "fcp_rsp_scsi_status", "0x%02x",
			     r->rsp_scsi_status);
		zfcp_dbf_out(&p, "fcp_rsp_resid", "0x%08x", r->rsp_resid);
		zfcp_dbf_out(&p, "fcp_rsp_code", "0x%08x", r->rsp_code);
		zfcp_dbf_out(&p, "fcp_sns_info_len", "0x%08x", r->sns_info_len);
		zfcp_dbf_outd(&p, "fcp_sns_info", r->sns_info,
			      min((int)r->sns_info_len,
			      ZFCP_DBF_SCSI_FCP_SNS_INFO), 0,
			      r->sns_info_len);
	}
	p += sprintf(p, "\n");
	return p - out_buf;
}