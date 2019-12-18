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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  fr_flags; int /*<<< orphan*/  fr_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  fr_rsp_len; } ;
struct fcp_resp_with_ext {TYPE_2__ resp; TYPE_1__ ext; } ;
struct fcp_resp_rsp_info {int rsp_code; } ;
struct fc_seq {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;int /*<<< orphan*/  (* exch_done ) (struct fc_seq*) ;int /*<<< orphan*/  (* seq_send ) (struct fc_lport*,struct fc_seq*,struct fc_frame*) ;} ;
struct fc_lport {TYPE_3__ tt; } ;
struct fc_frame_header {int /*<<< orphan*/  fh_ox_id; int /*<<< orphan*/  fh_s_id; } ;
struct fc_frame {int dummy; } ;
typedef  enum fcp_resp_rsp_codes { ____Placeholder_fcp_resp_rsp_codes } fcp_resp_rsp_codes ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_RSP_LEN_VAL ; 
 int /*<<< orphan*/  FC_RCTL_DD_CMD_STATUS ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,size_t) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame const*) ; 
 struct fcp_resp_with_ext* fc_frame_payload_get (struct fc_frame*,size_t) ; 
 struct fc_seq* fr_seq (struct fc_frame*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memset (struct fcp_resp_with_ext*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_seq*,struct fc_frame*) ; 
 int /*<<< orphan*/  stub2 (struct fc_seq*) ; 
 int /*<<< orphan*/  stub3 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void ft_send_resp_status(struct fc_lport *lport,
				const struct fc_frame *rx_fp,
				u32 status, enum fcp_resp_rsp_codes code)
{
	struct fc_frame *fp;
	struct fc_seq *sp;
	const struct fc_frame_header *fh;
	size_t len;
	struct fcp_resp_with_ext *fcp;
	struct fcp_resp_rsp_info *info;

	fh = fc_frame_header_get(rx_fp);
	pr_debug("FCP error response: did %x oxid %x status %x code %x\n",
		  ntoh24(fh->fh_s_id), ntohs(fh->fh_ox_id), status, code);
	len = sizeof(*fcp);
	if (status == SAM_STAT_GOOD)
		len += sizeof(*info);
	fp = fc_frame_alloc(lport, len);
	if (!fp)
		return;
	fcp = fc_frame_payload_get(fp, len);
	memset(fcp, 0, len);
	fcp->resp.fr_status = status;
	if (status == SAM_STAT_GOOD) {
		fcp->ext.fr_rsp_len = htonl(sizeof(*info));
		fcp->resp.fr_flags |= FCP_RSP_LEN_VAL;
		info = (struct fcp_resp_rsp_info *)(fcp + 1);
		info->rsp_code = code;
	}

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_DD_CMD_STATUS, 0);
	sp = fr_seq(fp);
	if (sp) {
		lport->tt.seq_send(lport, sp, fp);
		lport->tt.exch_done(sp);
	} else {
		lport->tt.frame_send(lport, fp);
	}
}