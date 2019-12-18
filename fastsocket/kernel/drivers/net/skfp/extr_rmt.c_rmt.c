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
struct TYPE_3__ {TYPE_2__* m; } ;
struct s_smc {TYPE_1__ mib; } ;
struct TYPE_4__ {int fddiMACRMTState; } ;

/* Variables and functions */
 int AFLAG ; 
 int /*<<< orphan*/  DB_RMT (char*,char*,int /*<<< orphan*/ ) ; 
 size_t MAC0 ; 
 char** rmt_events ; 
 int /*<<< orphan*/  rmt_fsm (struct s_smc*,int) ; 
 int /*<<< orphan*/  rmt_state_change (struct s_smc*,int) ; 
 int /*<<< orphan*/ * rmt_states ; 

void rmt(struct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_RMT("RMT : state %s%s",
			(smc->mib.m[MAC0].fddiMACRMTState & AFLAG) ? "ACTIONS " : "",
			rmt_states[smc->mib.m[MAC0].fddiMACRMTState & ~AFLAG]) ;
		DB_RMT(" event %s\n",rmt_events[event],0) ;
		state = smc->mib.m[MAC0].fddiMACRMTState ;
		rmt_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.m[MAC0].fddiMACRMTState) ;
	rmt_state_change(smc,(int)smc->mib.m[MAC0].fddiMACRMTState) ;
}