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
struct TYPE_3__ {scalar_t__ sas; } ;
struct s_smc {TYPE_2__* y; TYPE_1__ s; } ;
struct TYPE_4__ {scalar_t__ cem_pst; scalar_t__ wc_flag; scalar_t__ cf_join; } ;

/* Variables and functions */
 scalar_t__ CEM_PST_DOWN ; 
 scalar_t__ CEM_PST_HOLD ; 
 scalar_t__ CEM_PST_UP ; 
 int CF_JOIN ; 
 scalar_t__ EVENT_PCM ; 
 int PA ; 
 int PB ; 
 int /*<<< orphan*/  PC_START ; 
 scalar_t__ SMT_DAS ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cem_priv_state(struct s_smc *smc, int event)
/* State machine for private PORT states: used to optimize dual homing */
{
	int	np;	/* Number of the port */
	int	i;

	/* Do this only in a DAS */
	if (smc->s.sas != SMT_DAS )
		return ;

	np = event - CF_JOIN;

	if (np != PA && np != PB) {
		return ;
	}
	/* Change the port state according to the event (portnumber) */
	if (smc->y[np].cf_join) {
		smc->y[np].cem_pst = CEM_PST_UP ;
	} else if (!smc->y[np].wc_flag) {
		/* set the port to done only if it is not withheld */
		smc->y[np].cem_pst = CEM_PST_DOWN ;
	}

	/* Don't set an hold port to down */

	/* Check all ports of restart conditions */
	for (i = 0 ; i < 2 ; i ++ ) {
		/* Check all port for PORT is on hold and no withhold is done */
		if ( smc->y[i].cem_pst == CEM_PST_HOLD && !smc->y[i].wc_flag ) {
			smc->y[i].cem_pst = CEM_PST_DOWN;
			queue_event(smc,(int)(EVENT_PCM+i),PC_START) ;
		}
		if ( smc->y[i].cem_pst == CEM_PST_UP && smc->y[i].wc_flag ) {
			smc->y[i].cem_pst = CEM_PST_HOLD;
			queue_event(smc,(int)(EVENT_PCM+i),PC_START) ;
		}
		if ( smc->y[i].cem_pst == CEM_PST_DOWN && smc->y[i].wc_flag ) {
			/*
			 * The port must be restarted when the wc_flag
			 * will be reset. So set the port on hold.
			 */
			smc->y[i].cem_pst = CEM_PST_HOLD;
		}
	}
	return ;
}