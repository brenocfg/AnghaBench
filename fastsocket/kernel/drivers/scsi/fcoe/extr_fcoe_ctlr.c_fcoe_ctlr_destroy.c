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
struct fcoe_ctlr {int /*<<< orphan*/  timer_work; int /*<<< orphan*/  timer; int /*<<< orphan*/  ctlr_mutex; int /*<<< orphan*/  fip_recv_list; int /*<<< orphan*/  recv_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_ST_DISABLED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_ctlr_reset_fcfs (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_set_state (struct fcoe_ctlr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void fcoe_ctlr_destroy(struct fcoe_ctlr *fip)
{
	cancel_work_sync(&fip->recv_work);
	skb_queue_purge(&fip->fip_recv_list);

	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_set_state(fip, FIP_ST_DISABLED);
	fcoe_ctlr_reset_fcfs(fip);
	mutex_unlock(&fip->ctlr_mutex);
	del_timer_sync(&fip->timer);
	cancel_work_sync(&fip->timer_work);
}