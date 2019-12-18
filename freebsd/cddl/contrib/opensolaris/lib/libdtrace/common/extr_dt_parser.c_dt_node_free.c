#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar_t ;
struct TYPE_4__ {int dn_kind; int /*<<< orphan*/  dn_list; int /*<<< orphan*/ * dn_provname; int /*<<< orphan*/  dn_probes; struct TYPE_4__* dn_membexpr; int /*<<< orphan*/ * dn_membname; int /*<<< orphan*/  dn_acts; int /*<<< orphan*/  dn_pdescs; int /*<<< orphan*/ * dn_locals; struct TYPE_4__* dn_pred; int /*<<< orphan*/ * dn_desc; int /*<<< orphan*/ * dn_spec; int /*<<< orphan*/  dn_aggtup; struct TYPE_4__* dn_aggfun; struct TYPE_4__* dn_expr; struct TYPE_4__* dn_right; struct TYPE_4__* dn_left; struct TYPE_4__* dn_child; int /*<<< orphan*/  dn_args; TYPE_3__* dn_ident; int /*<<< orphan*/ * dn_string; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_5__ {int di_flags; } ;

/* Variables and functions */
 int DT_IDFLG_ORPHAN ; 
#define  DT_NODE_AGG 144 
#define  DT_NODE_CLAUSE 143 
#define  DT_NODE_DEXPR 142 
#define  DT_NODE_DFUNC 141 
 int DT_NODE_FREE ; 
#define  DT_NODE_FUNC 140 
#define  DT_NODE_IDENT 139 
#define  DT_NODE_MEMBER 138 
#define  DT_NODE_OP1 137 
#define  DT_NODE_OP2 136 
#define  DT_NODE_OP3 135 
#define  DT_NODE_PDESC 134 
#define  DT_NODE_PROBE 133 
#define  DT_NODE_PROG 132 
#define  DT_NODE_PROVIDER 131 
#define  DT_NODE_STRING 130 
#define  DT_NODE_TYPE 129 
#define  DT_NODE_VAR 128 
 int /*<<< orphan*/  dt_ident_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  dt_idhash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
dt_node_free(dt_node_t *dnp)
{
	uchar_t kind = dnp->dn_kind;

	dnp->dn_kind = DT_NODE_FREE;

	switch (kind) {
	case DT_NODE_STRING:
	case DT_NODE_IDENT:
	case DT_NODE_TYPE:
		free(dnp->dn_string);
		dnp->dn_string = NULL;
		break;

	case DT_NODE_VAR:
	case DT_NODE_FUNC:
	case DT_NODE_PROBE:
		if (dnp->dn_ident != NULL) {
			if (dnp->dn_ident->di_flags & DT_IDFLG_ORPHAN)
				dt_ident_destroy(dnp->dn_ident);
			dnp->dn_ident = NULL;
		}
		dt_node_list_free(&dnp->dn_args);
		break;

	case DT_NODE_OP1:
		if (dnp->dn_child != NULL) {
			dt_node_free(dnp->dn_child);
			dnp->dn_child = NULL;
		}
		break;

	case DT_NODE_OP3:
		if (dnp->dn_expr != NULL) {
			dt_node_free(dnp->dn_expr);
			dnp->dn_expr = NULL;
		}
		/*FALLTHRU*/
	case DT_NODE_OP2:
		if (dnp->dn_left != NULL) {
			dt_node_free(dnp->dn_left);
			dnp->dn_left = NULL;
		}
		if (dnp->dn_right != NULL) {
			dt_node_free(dnp->dn_right);
			dnp->dn_right = NULL;
		}
		break;

	case DT_NODE_DEXPR:
	case DT_NODE_DFUNC:
		if (dnp->dn_expr != NULL) {
			dt_node_free(dnp->dn_expr);
			dnp->dn_expr = NULL;
		}
		break;

	case DT_NODE_AGG:
		if (dnp->dn_aggfun != NULL) {
			dt_node_free(dnp->dn_aggfun);
			dnp->dn_aggfun = NULL;
		}
		dt_node_list_free(&dnp->dn_aggtup);
		break;

	case DT_NODE_PDESC:
		free(dnp->dn_spec);
		dnp->dn_spec = NULL;
		free(dnp->dn_desc);
		dnp->dn_desc = NULL;
		break;

	case DT_NODE_CLAUSE:
		if (dnp->dn_pred != NULL)
			dt_node_free(dnp->dn_pred);
		if (dnp->dn_locals != NULL)
			dt_idhash_destroy(dnp->dn_locals);
		dt_node_list_free(&dnp->dn_pdescs);
		dt_node_list_free(&dnp->dn_acts);
		break;

	case DT_NODE_MEMBER:
		free(dnp->dn_membname);
		dnp->dn_membname = NULL;
		if (dnp->dn_membexpr != NULL) {
			dt_node_free(dnp->dn_membexpr);
			dnp->dn_membexpr = NULL;
		}
		break;

	case DT_NODE_PROVIDER:
		dt_node_list_free(&dnp->dn_probes);
		free(dnp->dn_provname);
		dnp->dn_provname = NULL;
		break;

	case DT_NODE_PROG:
		dt_node_list_free(&dnp->dn_list);
		break;
	}
}