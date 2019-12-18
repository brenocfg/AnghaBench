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
struct TYPE_2__ {int /*<<< orphan*/  (* exch_mgr_reset ) (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disc_stop_final ) (struct fc_lport*) ;int /*<<< orphan*/  (* fcp_abort_io ) (struct fc_lport*) ;int /*<<< orphan*/  frame_send; } ;
struct fc_lport {int /*<<< orphan*/  retry_work; TYPE_1__ tt; int /*<<< orphan*/  lp_mutex; scalar_t__ link_up; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPORT_ST_DISABLED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_fc4_del_lport (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_frame_drop ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*) ; 
 int /*<<< orphan*/  stub2 (struct fc_lport*) ; 
 int /*<<< orphan*/  stub3 (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fc_lport_destroy(struct fc_lport *lport)
{
	mutex_lock(&lport->lp_mutex);
	lport->state = LPORT_ST_DISABLED;
	lport->link_up = 0;
	lport->tt.frame_send = fc_frame_drop;
	mutex_unlock(&lport->lp_mutex);

	lport->tt.fcp_abort_io(lport);
	lport->tt.disc_stop_final(lport);
	lport->tt.exch_mgr_reset(lport, 0, 0);
	cancel_delayed_work_sync(&lport->retry_work);
	fc_fc4_del_lport(lport);
	return 0;
}