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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {char* dn_provname; TYPE_3__* dn_provider; struct TYPE_9__* dn_link; int /*<<< orphan*/  dn_provred; struct TYPE_9__* dn_probes; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_11__ {TYPE_1__* pv_nodes; int /*<<< orphan*/  pv_flags; } ;
struct TYPE_10__ {TYPE_1__* pcb_list; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 size_t DTRACE_PROVNAMELEN ; 
 int /*<<< orphan*/  DT_NODE_PROVIDER ; 
 int /*<<< orphan*/  DT_PROVIDER_INTF ; 
 int /*<<< orphan*/  D_PROV_BADNAME ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  YYS_CLAUSE ; 
 int /*<<< orphan*/  dnerror (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 TYPE_3__* dt_provider_create (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* dt_provider_lookup (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  yybegin (int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

dt_node_t *
dt_node_provider(char *name, dt_node_t *probes)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dt_node_t *dnp = dt_node_alloc(DT_NODE_PROVIDER);
	dt_node_t *lnp;
	size_t len;

	dnp->dn_provname = name;
	dnp->dn_probes = probes;

	if (strchr(name, '`') != NULL) {
		dnerror(dnp, D_PROV_BADNAME, "provider name may not "
		    "contain scoping operator: %s\n", name);
	}

	if ((len = strlen(name)) >= DTRACE_PROVNAMELEN) {
		dnerror(dnp, D_PROV_BADNAME, "provider name may not exceed %d "
		    "characters: %s\n", DTRACE_PROVNAMELEN - 1, name);
	}

	if (isdigit(name[len - 1])) {
		dnerror(dnp, D_PROV_BADNAME, "provider name may not "
		    "end with a digit: %s\n", name);
	}

	/*
	 * Check to see if the provider is already defined or visible through
	 * dtrace(7D).  If so, set dn_provred to treat it as a re-declaration.
	 * If not, create a new provider and set its interface-only flag.  This
	 * flag may be cleared later by calls made to dt_probe_declare().
	 */
	if ((dnp->dn_provider = dt_provider_lookup(dtp, name)) != NULL)
		dnp->dn_provred = B_TRUE;
	else if ((dnp->dn_provider = dt_provider_create(dtp, name)) == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);
	else
		dnp->dn_provider->pv_flags |= DT_PROVIDER_INTF;

	/*
	 * Store all parse nodes created since we consumed the DT_KEY_PROVIDER
	 * token with the provider and then restore our lexing state to CLAUSE.
	 * Note that if dnp->dn_provred is true, we may end up storing dups of
	 * a provider's interface and implementation: we eat this space because
	 * the implementation will likely need to redeclare probe members, and
	 * therefore may result in those member nodes becoming persistent.
	 */
	for (lnp = yypcb->pcb_list; lnp->dn_link != NULL; lnp = lnp->dn_link)
		continue; /* skip to end of allocation list */

	lnp->dn_link = dnp->dn_provider->pv_nodes;
	dnp->dn_provider->pv_nodes = yypcb->pcb_list;

	yybegin(YYS_CLAUSE);
	return (dnp);
}