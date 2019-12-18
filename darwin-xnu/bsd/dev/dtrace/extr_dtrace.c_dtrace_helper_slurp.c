#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_29__ {TYPE_3__* p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_30__ {int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/  dtpd_provider; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
struct TYPE_31__ {int /*<<< orphan*/  dthps_generation; int /*<<< orphan*/  dthps_vstate; } ;
typedef  TYPE_3__ dtrace_helpers_t ;
struct TYPE_32__ {int dten_ndesc; TYPE_5__** dten_desc; } ;
typedef  TYPE_4__ dtrace_enabling_t ;
struct TYPE_33__ {TYPE_2__ dted_probe; } ;
typedef  TYPE_5__ dtrace_ecbdesc_t ;
struct TYPE_34__ {scalar_t__ dofs_type; } ;
typedef  TYPE_6__ dof_sec_t ;
struct TYPE_35__ {scalar_t__ dofhp_dof; int /*<<< orphan*/  dofhp_addr; } ;
typedef  TYPE_7__ dof_helper_t ;
struct TYPE_36__ {scalar_t__ dofh_secnum; int dofh_secsize; scalar_t__ dofh_secoff; } ;
typedef  TYPE_8__ dof_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DOF_SECT_PROVIDER ; 
 int /*<<< orphan*/  DTRACE_HELPER_ACTION_USTACK ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIT_STRNEQL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dtrace_dof_destroy (TYPE_8__*) ; 
 int /*<<< orphan*/  dtrace_dof_error (TYPE_8__*,char*) ; 
 int dtrace_dof_slurp (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_enabling_destroy (TYPE_4__*) ; 
 int dtrace_helper_action_add (TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  dtrace_helper_destroygen (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_helper_provider_add (TYPE_1__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  dtrace_helper_provider_register (TYPE_1__*,TYPE_3__*,TYPE_7__*) ; 
 scalar_t__ dtrace_helper_provider_validate (TYPE_8__*,TYPE_6__*) ; 
 TYPE_3__* dtrace_helpers_create (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_helper_slurp(proc_t* p, dof_hdr_t *dof, dof_helper_t *dhp)
{
	dtrace_helpers_t *help;
	dtrace_vstate_t *vstate;
	dtrace_enabling_t *enab = NULL;
	int i, gen, rv, nhelpers = 0, nprovs = 0, destroy = 1;
	uintptr_t daddr = (uintptr_t)dof;

	LCK_MTX_ASSERT(&dtrace_meta_lock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if ((help = p->p_dtrace_helpers) == NULL)
		help = dtrace_helpers_create(p);

	vstate = &help->dthps_vstate;

	if ((rv = dtrace_dof_slurp(dof, vstate, NULL, &enab,
	    dhp != NULL ? dhp->dofhp_addr : 0, B_FALSE)) != 0) {
		dtrace_dof_destroy(dof);
		return (rv);
	}

	/*
	 * Look for helper providers and validate their descriptions.
	 */
	if (dhp != NULL) {
		for (i = 0; (uint32_t)i < dof->dofh_secnum; i++) {
			dof_sec_t *sec = (dof_sec_t *)(uintptr_t)(daddr +
			    dof->dofh_secoff + i * dof->dofh_secsize);

			if (sec->dofs_type != DOF_SECT_PROVIDER)
				continue;

			if (dtrace_helper_provider_validate(dof, sec) != 0) {
				dtrace_enabling_destroy(enab);
				dtrace_dof_destroy(dof);
				return (-1);
			}

			nprovs++;
		}
	}

	/*
	 * Now we need to walk through the ECB descriptions in the enabling.
	 */
	for (i = 0; i < enab->dten_ndesc; i++) {
		dtrace_ecbdesc_t *ep = enab->dten_desc[i];
		dtrace_probedesc_t *desc = &ep->dted_probe;

		/* APPLE NOTE: Darwin employs size bounded string operation. */
		if (!LIT_STRNEQL(desc->dtpd_provider, "dtrace"))
			continue;

		if (!LIT_STRNEQL(desc->dtpd_mod, "helper"))
			continue;

		if (!LIT_STRNEQL(desc->dtpd_func, "ustack"))
			continue;

		if ((rv = dtrace_helper_action_add(p, DTRACE_HELPER_ACTION_USTACK,
		    ep)) != 0) {
			/*
			 * Adding this helper action failed -- we are now going
			 * to rip out the entire generation and return failure.
			 */
			(void) dtrace_helper_destroygen(p, help->dthps_generation);
			dtrace_enabling_destroy(enab);
			dtrace_dof_destroy(dof);
			return (-1);
		}

		nhelpers++;
	}

	if (nhelpers < enab->dten_ndesc)
		dtrace_dof_error(dof, "unmatched helpers");

	gen = help->dthps_generation++;
	dtrace_enabling_destroy(enab);

	if (dhp != NULL && nprovs > 0) {
		dhp->dofhp_dof = (uint64_t)(uintptr_t)dof;
		if (dtrace_helper_provider_add(p, dhp, gen) == 0) {
			lck_mtx_unlock(&dtrace_lock);
			dtrace_helper_provider_register(p, help, dhp);
			lck_mtx_lock(&dtrace_lock);

			destroy = 0;
		}
	}

	if (destroy)
		dtrace_dof_destroy(dof);

	return (gen);
}