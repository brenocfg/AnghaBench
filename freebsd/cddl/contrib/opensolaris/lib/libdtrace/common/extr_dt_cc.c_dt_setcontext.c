#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_21__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_probeinfo_t ;
struct TYPE_35__ {int /*<<< orphan*/  dtpd_id; int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/ * dtpd_provider; } ;
typedef  TYPE_5__ dtrace_probedesc_t ;
struct TYPE_36__ {int /*<<< orphan*/  dtpa_args; int /*<<< orphan*/  dtpa_name; int /*<<< orphan*/  dtpa_func; int /*<<< orphan*/  dtpa_mod; int /*<<< orphan*/  dtpa_provider; } ;
typedef  TYPE_6__ dtrace_pattr_t ;
struct TYPE_37__ {int /*<<< orphan*/  dt_globals; } ;
typedef  TYPE_7__ dtrace_hdl_t ;
struct TYPE_30__ {int dtpp_flags; } ;
struct TYPE_32__ {TYPE_1__ dtvd_priv; } ;
struct TYPE_38__ {TYPE_2__ pv_desc; } ;
typedef  TYPE_8__ dt_provider_t ;
struct TYPE_39__ {TYPE_4__* pr_pvp; } ;
typedef  TYPE_9__ dt_probe_t ;
struct TYPE_28__ {int /*<<< orphan*/  di_attr; } ;
typedef  TYPE_10__ dt_ident_t ;
typedef  int /*<<< orphan*/  attrstr ;
struct TYPE_33__ {TYPE_6__ dtvd_attr; } ;
struct TYPE_34__ {TYPE_3__ pv_desc; } ;
struct TYPE_31__ {int /*<<< orphan*/  dtp_argc; int /*<<< orphan*/  dtp_attr; int /*<<< orphan*/  dtp_arga; } ;
struct TYPE_29__ {int pcb_cflags; TYPE_9__* pcb_probe; TYPE_5__* pcb_pdesc; TYPE_21__ pcb_pinfo; int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int DTRACE_C_ZDEFS ; 
 int DTRACE_PRIV_PROC ; 
 int /*<<< orphan*/  D_PDESC_INVAL ; 
 int /*<<< orphan*/  D_PDESC_ZERO ; 
 int /*<<< orphan*/  EDT_COMPILER ; 
 int EDT_NOPROBE ; 
 int EDT_UNSTABLE ; 
 TYPE_6__ _dtrace_prvdesc ; 
 int /*<<< orphan*/  bzero (TYPE_21__*,int) ; 
 int /*<<< orphan*/  dt_attr_str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* dt_idhash_lookup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dt_pid_create_probes (TYPE_5__*,TYPE_7__*,TYPE_11__*) ; 
 TYPE_9__* dt_probe_info (TYPE_7__*,TYPE_5__*,TYPE_21__*) ; 
 TYPE_8__* dt_provider_lookup (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_errmsg (TYPE_7__*,int) ; 
 int dtrace_errno (TYPE_7__*) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_11__* yypcb ; 

void
dt_setcontext(dtrace_hdl_t *dtp, dtrace_probedesc_t *pdp)
{
	const dtrace_pattr_t *pap;
	dt_probe_t *prp;
	dt_provider_t *pvp;
	dt_ident_t *idp;
	char attrstr[8];
	int err;

	/*
	 * Both kernel and pid based providers are allowed to have names
	 * ending with what could be interpreted as a number. We assume it's
	 * a pid and that we may need to dynamically create probes for
	 * that process if:
	 *
	 * (1) The provider doesn't exist, or,
	 * (2) The provider exists and has DTRACE_PRIV_PROC privilege.
	 *
	 * On an error, dt_pid_create_probes() will set the error message
	 * and tag -- we just have to longjmp() out of here.
	 */
	if (isdigit(pdp->dtpd_provider[strlen(pdp->dtpd_provider) - 1]) &&
	    ((pvp = dt_provider_lookup(dtp, pdp->dtpd_provider)) == NULL ||
	    pvp->pv_desc.dtvd_priv.dtpp_flags & DTRACE_PRIV_PROC) &&
	    dt_pid_create_probes(pdp, dtp, yypcb) != 0) {
		longjmp(yypcb->pcb_jmpbuf, EDT_COMPILER);
	}

	/*
	 * Call dt_probe_info() to get the probe arguments and attributes.  If
	 * a representative probe is found, set 'pap' to the probe provider's
	 * attributes.  Otherwise set 'pap' to default Unstable attributes.
	 */
	if ((prp = dt_probe_info(dtp, pdp, &yypcb->pcb_pinfo)) == NULL) {
		pap = &_dtrace_prvdesc;
		err = dtrace_errno(dtp);
		bzero(&yypcb->pcb_pinfo, sizeof (dtrace_probeinfo_t));
		yypcb->pcb_pinfo.dtp_attr = pap->dtpa_provider;
		yypcb->pcb_pinfo.dtp_arga = pap->dtpa_args;
	} else {
		pap = &prp->pr_pvp->pv_desc.dtvd_attr;
		err = 0;
	}

	if (err == EDT_NOPROBE && !(yypcb->pcb_cflags & DTRACE_C_ZDEFS)) {
		xyerror(D_PDESC_ZERO, "probe description %s:%s:%s:%s does not "
		    "match any probes\n", pdp->dtpd_provider, pdp->dtpd_mod,
		    pdp->dtpd_func, pdp->dtpd_name);
	}

	if (err != EDT_NOPROBE && err != EDT_UNSTABLE && err != 0)
		xyerror(D_PDESC_INVAL, "%s\n", dtrace_errmsg(dtp, err));

	dt_dprintf("set context to %s:%s:%s:%s [%u] prp=%p attr=%s argc=%d\n",
	    pdp->dtpd_provider, pdp->dtpd_mod, pdp->dtpd_func, pdp->dtpd_name,
	    pdp->dtpd_id, (void *)prp, dt_attr_str(yypcb->pcb_pinfo.dtp_attr,
	    attrstr, sizeof (attrstr)), yypcb->pcb_pinfo.dtp_argc);

	/*
	 * Reset the stability attributes of D global variables that vary
	 * based on the attributes of the provider and context itself.
	 */
	if ((idp = dt_idhash_lookup(dtp->dt_globals, "probeprov")) != NULL)
		idp->di_attr = pap->dtpa_provider;
	if ((idp = dt_idhash_lookup(dtp->dt_globals, "probemod")) != NULL)
		idp->di_attr = pap->dtpa_mod;
	if ((idp = dt_idhash_lookup(dtp->dt_globals, "probefunc")) != NULL)
		idp->di_attr = pap->dtpa_func;
	if ((idp = dt_idhash_lookup(dtp->dt_globals, "probename")) != NULL)
		idp->di_attr = pap->dtpa_name;
	if ((idp = dt_idhash_lookup(dtp->dt_globals, "args")) != NULL)
		idp->di_attr = pap->dtpa_args;

	yypcb->pcb_pdesc = pdp;
	yypcb->pcb_probe = prp;
}