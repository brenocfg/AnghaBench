#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_10__ {scalar_t__ dtad_arg; int /*<<< orphan*/  dtad_kind; } ;
typedef  TYPE_2__ dtrace_actdesc_t ;
struct TYPE_11__ {scalar_t__ dn_value; int /*<<< orphan*/ * dn_list; } ;
typedef  TYPE_3__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_STACK ; 
 size_t DTRACEOPT_STACKFRAMES ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int /*<<< orphan*/  D_STACK_PROTO ; 
 int /*<<< orphan*/  D_STACK_SIZE ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dt_node_is_posconst (TYPE_3__*) ; 

__attribute__((used)) static void
dt_action_stack_args(dtrace_hdl_t *dtp, dtrace_actdesc_t *ap, dt_node_t *arg0)
{
	ap->dtad_kind = DTRACEACT_STACK;

	if (dtp->dt_options[DTRACEOPT_STACKFRAMES] != DTRACEOPT_UNSET) {
		ap->dtad_arg = dtp->dt_options[DTRACEOPT_STACKFRAMES];
	} else {
		ap->dtad_arg = 0;
	}

	if (arg0 != NULL) {
		if (arg0->dn_list != NULL) {
			dnerror(arg0, D_STACK_PROTO, "stack( ) prototype "
			    "mismatch: too many arguments\n");
		}

		if (dt_node_is_posconst(arg0) == 0) {
			dnerror(arg0, D_STACK_SIZE, "stack( ) size must be a "
			    "non-zero positive integral constant expression\n");
		}

		ap->dtad_arg = arg0->dn_value;
	}
}