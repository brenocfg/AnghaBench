#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* ddp_done ) (struct fc_lport*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  xfer_ddp; int /*<<< orphan*/  xfer_len; struct fc_lport* lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ) ; 

void fc_fcp_ddp_done(struct fc_fcp_pkt *fsp)
{
	struct fc_lport *lport;

	if (!fsp)
		return;

	if (fsp->xfer_ddp == FC_XID_UNKNOWN)
		return;

	lport = fsp->lp;
	if (lport->tt.ddp_done) {
		fsp->xfer_len = lport->tt.ddp_done(lport, fsp->xfer_ddp);
		fsp->xfer_ddp = FC_XID_UNKNOWN;
	}
}