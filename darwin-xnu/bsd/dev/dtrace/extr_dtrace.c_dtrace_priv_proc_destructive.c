#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dcr_action; } ;
struct TYPE_11__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_14__ {size_t cpu_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  p_lflag; } ;

/* Variables and functions */
 TYPE_9__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_UPRIV ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_CREDCHG ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 TYPE_8__* cpu_core ; 
 TYPE_6__* current_proc () ; 
 int /*<<< orphan*/  dtrace_can_attach_to_proc (TYPE_6__*) ; 
 scalar_t__ dtrace_is_restricted () ; 
 scalar_t__ dtrace_priv_proc_common_nocd () ; 
 scalar_t__ dtrace_priv_proc_common_user (TYPE_2__*) ; 
 scalar_t__ dtrace_priv_proc_common_zone (TYPE_2__*) ; 

__attribute__((used)) static int
dtrace_priv_proc_destructive(dtrace_state_t *state)
{
	int action = state->dts_cred.dcr_action;

	if (ISSET(current_proc()->p_lflag, P_LNOATTACH))
		goto bad;

	if (dtrace_is_restricted() && !dtrace_can_attach_to_proc(current_proc()))
		goto bad;

	if (((action & DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE) == 0) &&
	    dtrace_priv_proc_common_zone(state) == 0)
		goto bad;

	if (((action & DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER) == 0) &&
	    dtrace_priv_proc_common_user(state) == 0)
		goto bad;

	if (((action & DTRACE_CRA_PROC_DESTRUCTIVE_CREDCHG) == 0) &&
	    dtrace_priv_proc_common_nocd() == 0)
		goto bad;

	return (1);

bad:
	cpu_core[CPU->cpu_id].cpuc_dtrace_flags |= CPU_DTRACE_UPRIV;

	return (0);
}