#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fcp_cmnd {int fc_flags; int /*<<< orphan*/  fc_dl; } ;
struct fc_frame_header {scalar_t__ fh_r_ctl; int /*<<< orphan*/  fh_rx_id; } ;
struct fc_frame {int dummy; } ;
struct TYPE_3__ {scalar_t__ data_len; } ;

/* Variables and functions */
 int FCP_CFL_WRDATA ; 
 scalar_t__ FC_RCTL_DD_UNSOL_CMD ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 scalar_t__ fc_fcp_is_read (TYPE_1__*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fcp_cmnd* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fcoe_ddp_min ; 
 TYPE_1__* fr_fsp (struct fc_frame*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fcoe_oem_match(struct fc_frame *fp)
{
	struct fc_frame_header *fh = fc_frame_header_get(fp);
	struct fcp_cmnd *fcp;

	if (fc_fcp_is_read(fr_fsp(fp)) &&
	    (fr_fsp(fp)->data_len > fcoe_ddp_min))
		return true;
	else if ((fr_fsp(fp) == NULL) &&
		 (fh->fh_r_ctl == FC_RCTL_DD_UNSOL_CMD) &&
		 (ntohs(fh->fh_rx_id) == FC_XID_UNKNOWN)) {
		fcp = fc_frame_payload_get(fp, sizeof(*fcp));
		if ((fcp->fc_flags & FCP_CFL_WRDATA) &&
		    (ntohl(fcp->fc_dl) > fcoe_ddp_min))
			return true;
	}
	return false;
}