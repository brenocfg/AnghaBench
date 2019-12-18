#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {char* dn_spec; int /*<<< orphan*/ * dn_desc; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  pcb_sargv; int /*<<< orphan*/  pcb_sargc; int /*<<< orphan*/  pcb_pspec; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NODE_PDESC ; 
 int /*<<< orphan*/  D_PDESC_INVAL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_xstr2desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

dt_node_t *
dt_node_pdesc_by_name(char *spec)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dt_node_t *dnp;

	if (spec == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dnp = dt_node_alloc(DT_NODE_PDESC);
	dnp->dn_spec = spec;
	dnp->dn_desc = malloc(sizeof (dtrace_probedesc_t));

	if (dnp->dn_desc == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	if (dtrace_xstr2desc(dtp, yypcb->pcb_pspec, dnp->dn_spec,
	    yypcb->pcb_sargc, yypcb->pcb_sargv, dnp->dn_desc) != 0) {
		xyerror(D_PDESC_INVAL, "invalid probe description \"%s\": %s\n",
		    dnp->dn_spec, dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}

	free(dnp->dn_spec);
	dnp->dn_spec = NULL;

	return (dnp);
}