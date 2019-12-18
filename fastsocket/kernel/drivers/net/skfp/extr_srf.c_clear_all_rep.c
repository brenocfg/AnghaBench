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
struct s_srf_evc {void** evc_cond_state; int /*<<< orphan*/  evc_code; void* evc_rep_required; } ;
struct TYPE_2__ {void* any_report; } ;
struct s_smc {TYPE_1__ srf; struct s_srf_evc* evcs; } ;

/* Variables and functions */
 void* FALSE ; 
 unsigned int MAX_EVCS ; 
 scalar_t__ SMT_IS_CONDITION (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_all_rep(struct s_smc *smc)
{
	struct s_srf_evc	*evc ;
	int			i ;

	for (i = 0, evc = smc->evcs ; (unsigned) i < MAX_EVCS ; i++, evc++) {
		evc->evc_rep_required = FALSE ;
		if (SMT_IS_CONDITION(evc->evc_code))
			*evc->evc_cond_state = FALSE ;
	}
	smc->srf.any_report = FALSE ;
}