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
struct TYPE_2__ {scalar_t__ (* fcp_cmd_send ) (struct fc_lport*,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  timer; int /*<<< orphan*/  recov_retry; struct fc_lport* lp; } ;

/* Variables and functions */
 scalar_t__ FC_MAX_RECOV_RETRY ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_timer_set (struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_tm_done ; 
 int /*<<< orphan*/  get_fsp_rec_tov (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 scalar_t__ stub1 (struct fc_lport*,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_lun_reset_send(unsigned long data)
{
	struct fc_fcp_pkt *fsp = (struct fc_fcp_pkt *)data;
	struct fc_lport *lport = fsp->lp;

	if (lport->tt.fcp_cmd_send(lport, fsp, fc_tm_done)) {
		if (fsp->recov_retry++ >= FC_MAX_RECOV_RETRY)
			return;
		if (fc_fcp_lock_pkt(fsp))
			return;
		setup_timer(&fsp->timer, fc_lun_reset_send, (unsigned long)fsp);
		fc_fcp_timer_set(fsp, get_fsp_rec_tov(fsp));
		fc_fcp_unlock_pkt(fsp);
	}
}