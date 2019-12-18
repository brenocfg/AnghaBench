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
struct s_smc {int dummy; } ;
struct TYPE_2__ {scalar_t__ tm_active; } ;
struct s_phy {TYPE_1__ pcm_timer0; } ;

/* Variables and functions */
 int /*<<< orphan*/  smt_timer_stop (struct s_smc*,TYPE_1__*) ; 

__attribute__((used)) static void stop_pcm_timer0(struct s_smc *smc, struct s_phy *phy)
{
	if (phy->pcm_timer0.tm_active)
		smt_timer_stop(smc,&phy->pcm_timer0) ;
}