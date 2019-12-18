#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_11__ {size_t pr_xargc; int /*<<< orphan*/  pr_name; TYPE_2__* pr_inst; int /*<<< orphan*/  pr_nargc; TYPE_6__* pr_mapping; TYPE_3__* pr_xargs; TYPE_3__* pr_nargs; } ;
typedef  TYPE_1__ dt_probe_t ;
struct TYPE_12__ {scalar_t__ pi_noffs; scalar_t__ pi_nenoffs; int /*<<< orphan*/  pi_rname; TYPE_6__* pi_enoffs; TYPE_6__* pi_offs; int /*<<< orphan*/  pi_fname; struct TYPE_12__* pi_next; } ;
typedef  TYPE_2__ dt_probe_instance_t ;
struct TYPE_13__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; struct TYPE_13__* dn_list; } ;
typedef  TYPE_3__ dt_node_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_14__ {TYPE_1__* di_data; } ;
typedef  TYPE_4__ dt_ident_t ;
struct TYPE_15__ {int /*<<< orphan*/  ddo_probes; int /*<<< orphan*/  ddo_rels; int /*<<< orphan*/  ddo_enoffs; int /*<<< orphan*/  ddo_offs; int /*<<< orphan*/  ddo_args; int /*<<< orphan*/  ddo_strs; int /*<<< orphan*/ * ddo_hdl; } ;
typedef  TYPE_5__ dt_dof_t ;
typedef  int /*<<< orphan*/  dofr ;
typedef  int /*<<< orphan*/  dofpr ;
struct TYPE_16__ {int dofpr_nargv; int dofpr_xargv; int dofpr_argidx; size_t dofpr_xargc; int dofpr_offidx; scalar_t__ dofpr_noffs; int dofpr_enoffidx; scalar_t__ dofpr_nenoffs; int dofr_offset; scalar_t__ dofr_data; int /*<<< orphan*/  dofr_type; void* dofr_name; void* dofpr_func; scalar_t__ dofpr_pad2; scalar_t__ dofpr_pad1; int /*<<< orphan*/  dofpr_nargc; void* dofpr_name; scalar_t__ dofpr_addr; } ;
typedef  TYPE_6__ dof_relodesc_t ;
typedef  TYPE_6__ dof_probe_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DOF_RELO_DOFREL ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctf_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 void* dof_add_string (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int dt_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dof_add_probe(dt_idhash_t *dhp, dt_ident_t *idp, void *data)
{
	dt_dof_t *ddo = data;
	dtrace_hdl_t *dtp = ddo->ddo_hdl;
	dt_probe_t *prp = idp->di_data;

	dof_probe_t dofpr;
	dof_relodesc_t dofr;
	dt_probe_instance_t *pip;
	dt_node_t *dnp;

	char buf[DT_TYPE_NAMELEN];
	uint_t i;

	dofpr.dofpr_addr = 0;
	dofpr.dofpr_name = dof_add_string(ddo, prp->pr_name);
	dofpr.dofpr_nargv = dt_buf_len(&ddo->ddo_strs);

	for (dnp = prp->pr_nargs; dnp != NULL; dnp = dnp->dn_list) {
		(void) dof_add_string(ddo, ctf_type_name(dnp->dn_ctfp,
		    dnp->dn_type, buf, sizeof (buf)));
	}

	dofpr.dofpr_xargv = dt_buf_len(&ddo->ddo_strs);

	for (dnp = prp->pr_xargs; dnp != NULL; dnp = dnp->dn_list) {
		(void) dof_add_string(ddo, ctf_type_name(dnp->dn_ctfp,
		    dnp->dn_type, buf, sizeof (buf)));
	}

	dofpr.dofpr_argidx = dt_buf_len(&ddo->ddo_args) / sizeof (uint8_t);

	for (i = 0; i < prp->pr_xargc; i++) {
		dt_buf_write(dtp, &ddo->ddo_args, &prp->pr_mapping[i],
		    sizeof (uint8_t), sizeof (uint8_t));
	}

	dofpr.dofpr_nargc = prp->pr_nargc;
	dofpr.dofpr_xargc = prp->pr_xargc;
	dofpr.dofpr_pad1 = 0;
	dofpr.dofpr_pad2 = 0;

	for (pip = prp->pr_inst; pip != NULL; pip = pip->pi_next) {
		dt_dprintf("adding probe for %s:%s\n", pip->pi_fname,
		    prp->pr_name);

		dofpr.dofpr_func = dof_add_string(ddo, pip->pi_fname);

		/*
		 * There should be one probe offset or is-enabled probe offset
		 * or else this probe instance won't have been created. The
		 * kernel will reject DOF which has a probe with no offsets.
		 */
		assert(pip->pi_noffs + pip->pi_nenoffs > 0);

		dofpr.dofpr_offidx =
		    dt_buf_len(&ddo->ddo_offs) / sizeof (uint32_t);
		dofpr.dofpr_noffs = pip->pi_noffs;
		dt_buf_write(dtp, &ddo->ddo_offs, pip->pi_offs,
		    pip->pi_noffs * sizeof (uint32_t), sizeof (uint32_t));

		dofpr.dofpr_enoffidx =
		    dt_buf_len(&ddo->ddo_enoffs) / sizeof (uint32_t);
		dofpr.dofpr_nenoffs = pip->pi_nenoffs;
		dt_buf_write(dtp, &ddo->ddo_enoffs, pip->pi_enoffs,
		    pip->pi_nenoffs * sizeof (uint32_t), sizeof (uint32_t));

		dofr.dofr_name = dof_add_string(ddo, pip->pi_rname);
		dofr.dofr_type = DOF_RELO_DOFREL;
		dofr.dofr_offset = dt_buf_len(&ddo->ddo_probes);
		dofr.dofr_data = 0;

		dt_buf_write(dtp, &ddo->ddo_rels, &dofr,
		    sizeof (dofr), sizeof (uint64_t));

		dt_buf_write(dtp, &ddo->ddo_probes, &dofpr,
		    sizeof (dofpr), sizeof (uint64_t));
	}

	return (0);
}