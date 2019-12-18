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
struct net_device {struct claw_privbk* ml_priv; } ;
struct clawh {int /*<<< orphan*/  flag; } ;
struct claw_privbk {struct ccwbk* p_read_active_first; TYPE_2__* p_write_active_first; scalar_t__ p_claw_signal_blk; struct chbk* channel; } ;
struct chbk {int /*<<< orphan*/  cdev; int /*<<< orphan*/  IO_active; } ;
struct TYPE_6__ {scalar_t__ flag; } ;
struct ccwbk {int /*<<< orphan*/  read; TYPE_3__ header; } ;
typedef  unsigned long __u32 ;
struct TYPE_4__ {scalar_t__ flag; } ;
struct TYPE_5__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_BUSY ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_IDLE ; 
 scalar_t__ CLAW_PENDING ; 
 int LOCK_YES ; 
 size_t READ ; 
 int /*<<< orphan*/  ccw_check_return_code (int /*<<< orphan*/ ,int) ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
claw_strt_read (struct net_device *dev, int lock )
{
        int        rc = 0;
        __u32      parm;
        unsigned long  saveflags = 0;
	struct claw_privbk *privptr = dev->ml_priv;
        struct ccwbk*p_ccwbk;
        struct chbk *p_ch;
        struct clawh *p_clawh;
        p_ch=&privptr->channel[READ];

	CLAW_DBF_TEXT(4, trace, "StRdNter");
        p_clawh=(struct clawh *)privptr->p_claw_signal_blk;
        p_clawh->flag=CLAW_IDLE;    /* 0x00 */

        if ((privptr->p_write_active_first!=NULL &&
             privptr->p_write_active_first->header.flag!=CLAW_PENDING) ||
            (privptr->p_read_active_first!=NULL &&
             privptr->p_read_active_first->header.flag!=CLAW_PENDING )) {
                p_clawh->flag=CLAW_BUSY;    /* 0xff */
        }
        if (lock==LOCK_YES) {
                spin_lock_irqsave(get_ccwdev_lock(p_ch->cdev), saveflags);
        }
        if (test_and_set_bit(0, (void *)&p_ch->IO_active) == 0) {
		CLAW_DBF_TEXT(4, trace, "HotRead");
                p_ccwbk=privptr->p_read_active_first;
                parm = (unsigned long) p_ch;
                rc = ccw_device_start (p_ch->cdev, &p_ccwbk->read, parm,
				       0xff, 0);
                if (rc != 0) {
                        ccw_check_return_code(p_ch->cdev, rc);
                }
        }
	else {
		CLAW_DBF_TEXT(2, trace, "ReadAct");
	}

        if (lock==LOCK_YES) {
                spin_unlock_irqrestore(get_ccwdev_lock(p_ch->cdev), saveflags);
        }
	CLAW_DBF_TEXT(4, trace, "StRdExit");
        return;
}