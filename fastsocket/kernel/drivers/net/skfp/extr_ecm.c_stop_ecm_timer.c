#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tm_active; } ;
struct TYPE_3__ {TYPE_2__ ecm_timer; } ;
struct s_smc {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  smt_timer_stop (struct s_smc*,TYPE_2__*) ; 

__attribute__((used)) static void stop_ecm_timer(struct s_smc *smc)
{
	if (smc->e.ecm_timer.tm_active)
		smt_timer_stop(smc,&smc->e.ecm_timer) ;
}