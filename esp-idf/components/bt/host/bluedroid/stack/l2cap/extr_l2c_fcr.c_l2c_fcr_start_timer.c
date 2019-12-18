#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ in_use; } ;
struct TYPE_7__ {TYPE_6__ mon_retrans_timer; scalar_t__ wait_ack; } ;
struct TYPE_9__ {scalar_t__ rtrans_tout; scalar_t__ mon_tout; } ;
struct TYPE_8__ {TYPE_3__ fcr; } ;
struct TYPE_10__ {TYPE_1__ fcrb; TYPE_2__ our_cfg; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 int QUICK_TIMER_TICKS_PER_SEC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_quick_timer (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void l2c_fcr_start_timer (tL2C_CCB *p_ccb)
{
    assert(p_ccb != NULL);
    UINT32  tout;

    /* The timers which are in milliseconds */
    if (p_ccb->fcrb.wait_ack) {
        tout = (UINT32)p_ccb->our_cfg.fcr.mon_tout;
    } else {
        tout = (UINT32)p_ccb->our_cfg.fcr.rtrans_tout;
    }

    /* Only start a timer that was not started */
    if (p_ccb->fcrb.mon_retrans_timer.in_use == 0) {
        btu_start_quick_timer (&p_ccb->fcrb.mon_retrans_timer, BTU_TTYPE_L2CAP_CHNL, tout * QUICK_TIMER_TICKS_PER_SEC / 1000);
    }
}