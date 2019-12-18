#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dtsp_num_ifs; } ;
typedef  TYPE_2__ dt_sugar_parse_t ;
struct TYPE_10__ {int dn_kind; struct TYPE_10__* dn_list; struct TYPE_10__* dn_alternate_body; struct TYPE_10__* dn_body; struct TYPE_10__* dn_conditional; struct TYPE_10__* dn_probes; struct TYPE_10__* dn_members; struct TYPE_10__* dn_membexpr; TYPE_1__* dn_ident; struct TYPE_10__* dn_acts; struct TYPE_10__* dn_pred; struct TYPE_10__* dn_pdescs; struct TYPE_10__* dn_aggfun; struct TYPE_10__* dn_aggtup; struct TYPE_10__* dn_expr; struct TYPE_10__* dn_right; struct TYPE_10__* dn_left; int /*<<< orphan*/  dn_op; struct TYPE_10__* dn_child; struct TYPE_10__* dn_args; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_11__ {TYPE_3__* din_root; } ;
typedef  TYPE_4__ dt_idnode_t ;
struct TYPE_8__ {TYPE_4__* di_iarg; } ;

/* Variables and functions */
#define  DT_NODE_AGG 149 
#define  DT_NODE_CLAUSE 148 
#define  DT_NODE_DEXPR 147 
#define  DT_NODE_DFUNC 146 
#define  DT_NODE_FREE 145 
#define  DT_NODE_FUNC 144 
#define  DT_NODE_IDENT 143 
#define  DT_NODE_IF 142 
#define  DT_NODE_INLINE 141 
#define  DT_NODE_INT 140 
#define  DT_NODE_MEMBER 139 
#define  DT_NODE_OP1 138 
#define  DT_NODE_OP2 137 
#define  DT_NODE_OP3 136 
#define  DT_NODE_PDESC 135 
#define  DT_NODE_PROBE 134 
#define  DT_NODE_PROG 133 
#define  DT_NODE_PROVIDER 132 
#define  DT_NODE_STRING 131 
#define  DT_NODE_SYM 130 
#define  DT_NODE_TYPE 129 
#define  DT_NODE_XLATOR 128 
 int /*<<< orphan*/  DT_TOK_LBRAC ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 int /*<<< orphan*/  dnerror (TYPE_3__*,int /*<<< orphan*/ ,char*,void*,int) ; 

__attribute__((used)) static void
dt_sugar_visit_all(dt_sugar_parse_t *dp, dt_node_t *dnp)
{
	dt_node_t *arg;

	switch (dnp->dn_kind) {
	case DT_NODE_FREE:
	case DT_NODE_INT:
	case DT_NODE_STRING:
	case DT_NODE_SYM:
	case DT_NODE_TYPE:
	case DT_NODE_PROBE:
	case DT_NODE_PDESC:
	case DT_NODE_IDENT:
		break;

	case DT_NODE_FUNC:
		for (arg = dnp->dn_args; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		break;

	case DT_NODE_OP1:
		dt_sugar_visit_all(dp, dnp->dn_child);
		break;

	case DT_NODE_OP2:
		dt_sugar_visit_all(dp, dnp->dn_left);
		dt_sugar_visit_all(dp, dnp->dn_right);
		if (dnp->dn_op == DT_TOK_LBRAC) {
			dt_node_t *ln = dnp->dn_right;
			while (ln->dn_list != NULL) {
				dt_sugar_visit_all(dp, ln->dn_list);
				ln = ln->dn_list;
			}
		}
		break;

	case DT_NODE_OP3:
		dt_sugar_visit_all(dp, dnp->dn_expr);
		dt_sugar_visit_all(dp, dnp->dn_left);
		dt_sugar_visit_all(dp, dnp->dn_right);
		break;

	case DT_NODE_DEXPR:
	case DT_NODE_DFUNC:
		dt_sugar_visit_all(dp, dnp->dn_expr);
		break;

	case DT_NODE_AGG:
		for (arg = dnp->dn_aggtup; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);

		if (dnp->dn_aggfun)
			dt_sugar_visit_all(dp, dnp->dn_aggfun);
		break;

	case DT_NODE_CLAUSE:
		for (arg = dnp->dn_pdescs; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);

		if (dnp->dn_pred != NULL)
			dt_sugar_visit_all(dp, dnp->dn_pred);

		for (arg = dnp->dn_acts; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		break;

	case DT_NODE_INLINE: {
		const dt_idnode_t *inp = dnp->dn_ident->di_iarg;

		dt_sugar_visit_all(dp, inp->din_root);
		break;
	}
	case DT_NODE_MEMBER:
		if (dnp->dn_membexpr)
			dt_sugar_visit_all(dp, dnp->dn_membexpr);
		break;

	case DT_NODE_XLATOR:
		for (arg = dnp->dn_members; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		break;

	case DT_NODE_PROVIDER:
		for (arg = dnp->dn_probes; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		break;

	case DT_NODE_PROG:
		for (arg = dnp->dn_list; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		break;

	case DT_NODE_IF:
		dp->dtsp_num_ifs++;
		dt_sugar_visit_all(dp, dnp->dn_conditional);

		for (arg = dnp->dn_body; arg != NULL; arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);
		for (arg = dnp->dn_alternate_body; arg != NULL;
		    arg = arg->dn_list)
			dt_sugar_visit_all(dp, arg);

		break;

	default:
		(void) dnerror(dnp, D_UNKNOWN, "bad node %p, kind %d\n",
		    (void *)dnp, dnp->dn_kind);
	}
}