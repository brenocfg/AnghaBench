#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_28__ {TYPE_4__* dn_expr; } ;
typedef  TYPE_2__ dt_node_t ;
struct TYPE_29__ {TYPE_1__* dn_ident; } ;
struct TYPE_27__ {int di_id; int /*<<< orphan*/  di_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEACT_FREOPEN ; 
 int /*<<< orphan*/  DTRACEACT_MOD ; 
 int /*<<< orphan*/  DTRACEACT_PRINTF ; 
 int /*<<< orphan*/  DTRACEACT_SYM ; 
 int /*<<< orphan*/  DTRACEACT_SYSTEM ; 
 int /*<<< orphan*/  DTRACEACT_UADDR ; 
 int /*<<< orphan*/  DTRACEACT_UMOD ; 
 int /*<<< orphan*/  DTRACEACT_USYM ; 
#define  DT_ACT_BREAKPOINT 158 
#define  DT_ACT_CHILL 157 
#define  DT_ACT_CLEAR 156 
#define  DT_ACT_COMMIT 155 
#define  DT_ACT_DENORMALIZE 154 
#define  DT_ACT_DISCARD 153 
#define  DT_ACT_EXIT 152 
#define  DT_ACT_FREOPEN 151 
#define  DT_ACT_FTRUNCATE 150 
#define  DT_ACT_JSTACK 149 
#define  DT_ACT_MOD 148 
#define  DT_ACT_NORMALIZE 147 
#define  DT_ACT_PANIC 146 
#define  DT_ACT_PRINT 145 
#define  DT_ACT_PRINTA 144 
#define  DT_ACT_PRINTF 143 
#define  DT_ACT_PRINTM 142 
#define  DT_ACT_RAISE 141 
#define  DT_ACT_SETOPT 140 
#define  DT_ACT_SPECULATE 139 
#define  DT_ACT_STACK 138 
#define  DT_ACT_STOP 137 
#define  DT_ACT_SYM 136 
#define  DT_ACT_SYSTEM 135 
#define  DT_ACT_TRACE 134 
#define  DT_ACT_TRACEMEM 133 
#define  DT_ACT_TRUNC 132 
#define  DT_ACT_UADDR 131 
#define  DT_ACT_UMOD 130 
#define  DT_ACT_USTACK 129 
#define  DT_ACT_USYM 128 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  dnerror (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_action_breakpoint (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_chill (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_clear (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_commit (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_discard (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_exit (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_ftruncate (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_normalize (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_panic (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_printa (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_printflike (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_action_printm (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_raise (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_setopt (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_speculate (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_stack (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_stop (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_symmod (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_action_trace (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_tracemem (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_trunc (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_action_ustack (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_compile_fun(dtrace_hdl_t *dtp, dt_node_t *dnp, dtrace_stmtdesc_t *sdp)
{
	switch (dnp->dn_expr->dn_ident->di_id) {
	case DT_ACT_BREAKPOINT:
		dt_action_breakpoint(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_CHILL:
		dt_action_chill(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_CLEAR:
		dt_action_clear(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_COMMIT:
		dt_action_commit(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_DENORMALIZE:
		dt_action_normalize(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_DISCARD:
		dt_action_discard(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_EXIT:
		dt_action_exit(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_FREOPEN:
		dt_action_printflike(dtp, dnp->dn_expr, sdp, DTRACEACT_FREOPEN);
		break;
	case DT_ACT_FTRUNCATE:
		dt_action_ftruncate(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_MOD:
		dt_action_symmod(dtp, dnp->dn_expr, sdp, DTRACEACT_MOD);
		break;
	case DT_ACT_NORMALIZE:
		dt_action_normalize(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_PANIC:
		dt_action_panic(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_PRINT:
		dt_action_trace(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_PRINTA:
		dt_action_printa(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_PRINTF:
		dt_action_printflike(dtp, dnp->dn_expr, sdp, DTRACEACT_PRINTF);
		break;
	case DT_ACT_PRINTM:
		dt_action_printm(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_RAISE:
		dt_action_raise(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_SETOPT:
		dt_action_setopt(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_SPECULATE:
		dt_action_speculate(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_STACK:
		dt_action_stack(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_STOP:
		dt_action_stop(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_SYM:
		dt_action_symmod(dtp, dnp->dn_expr, sdp, DTRACEACT_SYM);
		break;
	case DT_ACT_SYSTEM:
		dt_action_printflike(dtp, dnp->dn_expr, sdp, DTRACEACT_SYSTEM);
		break;
	case DT_ACT_TRACE:
		dt_action_trace(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_TRACEMEM:
		dt_action_tracemem(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_TRUNC:
		dt_action_trunc(dtp, dnp->dn_expr, sdp);
		break;
	case DT_ACT_UADDR:
		dt_action_symmod(dtp, dnp->dn_expr, sdp, DTRACEACT_UADDR);
		break;
	case DT_ACT_UMOD:
		dt_action_symmod(dtp, dnp->dn_expr, sdp, DTRACEACT_UMOD);
		break;
	case DT_ACT_USYM:
		dt_action_symmod(dtp, dnp->dn_expr, sdp, DTRACEACT_USYM);
		break;
	case DT_ACT_USTACK:
	case DT_ACT_JSTACK:
		dt_action_ustack(dtp, dnp->dn_expr, sdp);
		break;
	default:
		dnerror(dnp->dn_expr, D_UNKNOWN, "tracing function %s( ) is "
		    "not yet supported\n", dnp->dn_expr->dn_ident->di_name);
	}
}