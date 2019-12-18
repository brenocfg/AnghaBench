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
struct fcoe_ctlr {int mode; int /*<<< orphan*/  fip_recv_list; int /*<<< orphan*/  recv_work; int /*<<< orphan*/  timer_work; int /*<<< orphan*/  timer; int /*<<< orphan*/  flogi_oxid; int /*<<< orphan*/  ctlr_lock; int /*<<< orphan*/  ctlr_mutex; int /*<<< orphan*/  fcfs; } ;
typedef  enum fip_state { ____Placeholder_fip_state } fip_state ;

/* Variables and functions */
 int /*<<< orphan*/  FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  FIP_ST_LINK_WAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_recv_work ; 
 int /*<<< orphan*/  fcoe_ctlr_set_state (struct fcoe_ctlr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_timeout ; 
 int /*<<< orphan*/  fcoe_ctlr_timer_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void fcoe_ctlr_init(struct fcoe_ctlr *fip, enum fip_state mode)
{
	fcoe_ctlr_set_state(fip, FIP_ST_LINK_WAIT);
	fip->mode = mode;
	INIT_LIST_HEAD(&fip->fcfs);
	mutex_init(&fip->ctlr_mutex);
	spin_lock_init(&fip->ctlr_lock);
	fip->flogi_oxid = FC_XID_UNKNOWN;
	setup_timer(&fip->timer, fcoe_ctlr_timeout, (unsigned long)fip);
	INIT_WORK(&fip->timer_work, fcoe_ctlr_timer_work);
	INIT_WORK(&fip->recv_work, fcoe_ctlr_recv_work);
	skb_queue_head_init(&fip->fip_recv_list);
}