#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dcr_action; } ;
struct TYPE_9__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_12__ {size_t cpu_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  p_lflag; } ;

/* Variables and functions */
 TYPE_7__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_UPRIV ; 
 int DTRACE_CRA_PROC ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 TYPE_6__* cpu_core ; 
 TYPE_4__* current_proc () ; 
 int /*<<< orphan*/  dtrace_are_restrictions_relaxed () ; 
 int /*<<< orphan*/  dtrace_can_attach_to_proc (TYPE_4__*) ; 
 scalar_t__ dtrace_is_restricted () ; 

__attribute__((used)) static int
dtrace_priv_proc(dtrace_state_t *state)
{
	if (ISSET(current_proc()->p_lflag, P_LNOATTACH))
		goto bad;

	if (dtrace_is_restricted() && !dtrace_are_restrictions_relaxed() && !dtrace_can_attach_to_proc(current_proc()))
		goto bad;

	if (state->dts_cred.dcr_action & DTRACE_CRA_PROC)
		return (1);

bad:
	cpu_core[CPU->cpu_id].cpuc_dtrace_flags |= CPU_DTRACE_UPRIV;

	return (0);
}