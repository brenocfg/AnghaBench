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
struct TYPE_4__ {int /*<<< orphan*/  ecm_line_state; scalar_t__ sb_flag; scalar_t__ trace_prop; int /*<<< orphan*/  path_test; } ;
struct TYPE_3__ {int /*<<< orphan*/  fddiSMTECMState; } ;
struct s_smc {TYPE_2__ e; TYPE_1__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC0_OUT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PT_PASSED ; 

void ecm_init(struct s_smc *smc)
{
	smc->e.path_test = PT_PASSED ;
	smc->e.trace_prop = 0 ;
	smc->e.sb_flag = 0 ;
	smc->mib.fddiSMTECMState = ACTIONS(EC0_OUT) ;
	smc->e.ecm_line_state = FALSE ;
}