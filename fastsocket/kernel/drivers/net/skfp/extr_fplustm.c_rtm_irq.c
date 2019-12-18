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
typedef  int /*<<< orphan*/  u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AIX_EVENT (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_RTM_CRTL ; 
 int /*<<< orphan*/  DB_RMT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FDDI_RING_STATUS ; 
 scalar_t__ FDDI_RTT ; 
 scalar_t__ FDDI_SMT_EVENT ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_CMDREG1 ; 
 int /*<<< orphan*/  FM_ICL ; 
 int /*<<< orphan*/  TIM_CL_IRQ ; 
 int TIM_RES_TOK ; 
 int /*<<< orphan*/  TIM_START ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_get_event_word (struct s_smc*) ; 

void rtm_irq(struct s_smc *smc)
{
	outpw(ADDR(B2_RTM_CRTL),TIM_CL_IRQ) ;		/* clear IRQ */
	if (inpw(ADDR(B2_RTM_CRTL)) & TIM_RES_TOK) {
		outpw(FM_A(FM_CMDREG1),FM_ICL) ;	/* force claim */
		DB_RMT("RMT: fddiPATHT_Rmode expired\n",0,0) ;
		AIX_EVENT(smc, (u_long) FDDI_RING_STATUS,
				(u_long) FDDI_SMT_EVENT,
				(u_long) FDDI_RTT, smt_get_event_word(smc));
	}
	outpw(ADDR(B2_RTM_CRTL),TIM_START) ;	/* enable RTM monitoring */
}