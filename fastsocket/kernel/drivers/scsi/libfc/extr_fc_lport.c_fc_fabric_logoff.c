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
struct TYPE_2__ {int /*<<< orphan*/  (* rport_flush_queue ) () ;int /*<<< orphan*/  (* rport_logoff ) (scalar_t__) ;int /*<<< orphan*/  (* disc_stop_final ) (struct fc_lport*) ;} ;
struct fc_lport {int /*<<< orphan*/  retry_work; int /*<<< orphan*/  lp_mutex; TYPE_1__ tt; scalar_t__ dns_rdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_lport_enter_logo (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 () ; 

int fc_fabric_logoff(struct fc_lport *lport)
{
	lport->tt.disc_stop_final(lport);
	mutex_lock(&lport->lp_mutex);
	if (lport->dns_rdata)
		lport->tt.rport_logoff(lport->dns_rdata);
	mutex_unlock(&lport->lp_mutex);
	lport->tt.rport_flush_queue();
	mutex_lock(&lport->lp_mutex);
	fc_lport_enter_logo(lport);
	mutex_unlock(&lport->lp_mutex);
	cancel_delayed_work_sync(&lport->retry_work);
	return 0;
}