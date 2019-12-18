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
struct TYPE_2__ {int /*<<< orphan*/  l3m_timer; } ;
struct PStack {scalar_t__ protocol; TYPE_1__ l3; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DREL_TIMER_VALUE ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISDN_PTYPE_NI1 ; 
 int /*<<< orphan*/  ST_L3_LC_REL_DELAY ; 

__attribute__((used)) static void
lc_start_delay_check(struct FsmInst *fi, int event, void *arg)
/* 20/09/00 - GE timer not user for NI-1 as layer 2 should stay up */
{
       struct PStack *st = fi->userdata;

       FsmChangeState(fi, ST_L3_LC_REL_DELAY);
       /* 19/09/00 - GE timer not user for NI-1 */
       if (st->protocol != ISDN_PTYPE_NI1) 
       		FsmAddTimer(&st->l3.l3m_timer, DREL_TIMER_VALUE, EV_TIMEOUT, NULL, 50);
}