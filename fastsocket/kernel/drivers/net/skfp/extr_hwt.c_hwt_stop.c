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
struct TYPE_2__ {int /*<<< orphan*/  timer_activ; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_TI_CRTL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TIM_CL_IRQ ; 
 int /*<<< orphan*/  TIM_STOP ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hwt_stop(struct s_smc *smc)
{
	outpw(ADDR(B2_TI_CRTL), TIM_STOP) ;
	outpw(ADDR(B2_TI_CRTL), TIM_CL_IRQ) ;

	smc->hw.timer_activ = FALSE ;
}