#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_17__ {int /*<<< orphan*/  di_attr; } ;
struct TYPE_18__ {size_t dx_id; TYPE_2__ dx_souid; int /*<<< orphan*/  dx_dst_type; int /*<<< orphan*/  dx_dst_ctfp; int /*<<< orphan*/  dx_src_type; int /*<<< orphan*/  dx_src_ctfp; int /*<<< orphan*/ * dx_membdif; TYPE_4__* dx_members; } ;
typedef  TYPE_3__ dt_xlator_t ;
struct TYPE_19__ {size_t dn_membid; int /*<<< orphan*/  dn_membname; struct TYPE_19__* dn_list; } ;
typedef  TYPE_4__ dt_node_t ;
struct TYPE_20__ {int /*<<< orphan*/  ddo_strsec; int /*<<< orphan*/  ddo_xlms; int /*<<< orphan*/  ddo_ldata; TYPE_1__* ddo_pgp; scalar_t__* ddo_xlexport; scalar_t__* ddo_xlimport; int /*<<< orphan*/ * ddo_hdl; } ;
typedef  TYPE_5__ dt_dof_t ;
typedef  int /*<<< orphan*/  dofxm ;
typedef  int /*<<< orphan*/  dofxl ;
struct TYPE_21__ {int /*<<< orphan*/  dofxm_type; void* dofxm_name; scalar_t__ dofxm_difo; } ;
typedef  TYPE_6__ dof_xlmember_t ;
struct TYPE_22__ {int dofxl_argc; int /*<<< orphan*/  dofxl_attr; void* dofxl_type; void* dofxl_argv; int /*<<< orphan*/  dofxl_strtab; scalar_t__ dofxl_members; } ;
typedef  TYPE_7__ dof_xlator_t ;
typedef  scalar_t__ dof_secidx_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_16__ {int /*<<< orphan*/ * dp_xrefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TEST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DOF_SECIDX_NONE ; 
 scalar_t__ DOF_SECT_XLEXPORT ; 
 scalar_t__ DOF_SECT_XLIMPORT ; 
 scalar_t__ DOF_SECT_XLMEMBERS ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ctf_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ dof_add_difo (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dof_add_lsect (TYPE_5__*,TYPE_7__*,scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 void* dof_add_string (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dof_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_buf_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int dt_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_buf_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  dt_node_diftype (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dof_add_translator(dt_dof_t *ddo, const dt_xlator_t *dxp, uint_t type)
{
	dtrace_hdl_t *dtp = ddo->ddo_hdl;
	dof_xlmember_t dofxm;
	dof_xlator_t dofxl;
	dof_secidx_t *xst;

	char buf[DT_TYPE_NAMELEN];
	dt_node_t *dnp;
	uint_t i = 0;

	assert(type == DOF_SECT_XLIMPORT || type == DOF_SECT_XLEXPORT);
	xst = type == DOF_SECT_XLIMPORT ? ddo->ddo_xlimport : ddo->ddo_xlexport;

	if (xst[dxp->dx_id] != DOF_SECIDX_NONE)
		return; /* translator has already been emitted */

	dt_buf_reset(dtp, &ddo->ddo_xlms);

	/*
	 * Generate an array of dof_xlmember_t's into ddo_xlms.  If we are
	 * importing the translator, add only those members referenced by the
	 * program and set the dofxm_difo reference of each member to NONE.  If
	 * we're exporting the translator, add all members and a DIFO for each.
	 */
	for (dnp = dxp->dx_members; dnp != NULL; dnp = dnp->dn_list, i++) {
		if (type == DOF_SECT_XLIMPORT) {
			if (!BT_TEST(ddo->ddo_pgp->dp_xrefs[dxp->dx_id], i))
				continue; /* member is not referenced */
			dofxm.dofxm_difo = DOF_SECIDX_NONE;
		} else {
			dofxm.dofxm_difo = dof_add_difo(ddo,
			    dxp->dx_membdif[dnp->dn_membid]);
		}

		dofxm.dofxm_name = dof_add_string(ddo, dnp->dn_membname);
		dt_node_diftype(dtp, dnp, &dofxm.dofxm_type);

		dt_buf_write(dtp, &ddo->ddo_xlms,
		    &dofxm, sizeof (dofxm), sizeof (uint32_t));
	}

	dofxl.dofxl_members = dof_add_lsect(ddo, NULL, DOF_SECT_XLMEMBERS,
	    sizeof (uint32_t), 0, sizeof (dofxm), dt_buf_len(&ddo->ddo_xlms));

	dt_buf_concat(dtp, &ddo->ddo_ldata, &ddo->ddo_xlms, sizeof (uint32_t));

	dofxl.dofxl_strtab = ddo->ddo_strsec;
	dofxl.dofxl_argv = dof_add_string(ddo, ctf_type_name(
	    dxp->dx_src_ctfp, dxp->dx_src_type, buf, sizeof (buf)));
	dofxl.dofxl_argc = 1;
	dofxl.dofxl_type = dof_add_string(ddo, ctf_type_name(
	    dxp->dx_dst_ctfp, dxp->dx_dst_type, buf, sizeof (buf)));
	dofxl.dofxl_attr = dof_attr(&dxp->dx_souid.di_attr);

	xst[dxp->dx_id] = dof_add_lsect(ddo, &dofxl, type,
	    sizeof (uint32_t), 0, 0, sizeof (dofxl));
}