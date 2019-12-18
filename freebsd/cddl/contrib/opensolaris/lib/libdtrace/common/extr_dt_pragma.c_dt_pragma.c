#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dt_pragmadesc {char* dpd_name; int dpd_kind; int /*<<< orphan*/  (* dpd_func ) (char*,TYPE_1__*) ;} ;
struct TYPE_6__ {scalar_t__ dn_kind; char* dn_string; struct TYPE_6__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 scalar_t__ DT_NODE_IDENT ; 
 scalar_t__ DT_NODE_INT ; 
#define  DT_PRAGMA_DCP 130 
#define  DT_PRAGMA_DIR 129 
#define  DT_PRAGMA_SUB 128 
 int /*<<< orphan*/  D_PRAGCTL_INVAL ; 
 int /*<<< orphan*/  D_PRAGMA_INVAL ; 
 int /*<<< orphan*/  dt_node_list_free (TYPE_1__**) ; 
 int /*<<< orphan*/  dt_pragma_line (char*,TYPE_1__*) ; 
 struct dt_pragmadesc* dt_pragmas ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  yylineno ; 

void
dt_pragma(dt_node_t *pnp)
{
	const struct dt_pragmadesc *dpd;
	dt_node_t *dnp;
	int kind = DT_PRAGMA_DIR;

	for (dnp = pnp; dnp != NULL; dnp = dnp->dn_list) {
		if (dnp->dn_kind == DT_NODE_INT) {
			dt_pragma_line("line", dnp);
			break;
		}

		if (dnp->dn_kind != DT_NODE_IDENT)
			xyerror(D_PRAGCTL_INVAL, "invalid control directive\n");

		if (kind == DT_PRAGMA_DIR &&
		    strcmp(dnp->dn_string, "pragma") == 0) {
			kind = DT_PRAGMA_SUB;
			continue;
		}

		if (kind == DT_PRAGMA_SUB &&
		    strcmp(dnp->dn_string, "D") == 0) {
			kind = DT_PRAGMA_DCP;
			continue;
		}

		for (dpd = dt_pragmas; dpd->dpd_name != NULL; dpd++) {
			if (dpd->dpd_kind <= kind &&
			    strcmp(dpd->dpd_name, dnp->dn_string) == 0)
				break;
		}

		yylineno--; /* since we've already seen \n */

		if (dpd->dpd_name != NULL) {
			dpd->dpd_func(dpd->dpd_name, dnp->dn_list);
			yylineno++;
			break;
		}

		switch (kind) {
		case DT_PRAGMA_DIR:
			xyerror(D_PRAGCTL_INVAL, "invalid control directive: "
			    "#%s\n", dnp->dn_string);
			/*NOTREACHED*/
		case DT_PRAGMA_SUB:
			break; /* K&R[A12.8] says to ignore unknown pragmas */
		case DT_PRAGMA_DCP:
		default:
			xyerror(D_PRAGMA_INVAL, "invalid D pragma: %s\n",
			    dnp->dn_string);
		}

		yylineno++;
		break;
	}

	dt_node_list_free(&pnp);
}