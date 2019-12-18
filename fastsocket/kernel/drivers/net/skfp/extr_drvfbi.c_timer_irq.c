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
struct TYPE_2__ {int /*<<< orphan*/  t_start; int /*<<< orphan*/  t_stop; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwt_restart (struct s_smc*) ; 
 int /*<<< orphan*/  smt_timer_done (struct s_smc*) ; 

void timer_irq(struct s_smc *smc)
{
	hwt_restart(smc);
	smc->hw.t_stop = smc->hw.t_start;
	smt_timer_done(smc) ;
}