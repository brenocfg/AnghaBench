#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  dtrace_difv_t ;
typedef  int /*<<< orphan*/  dtrace_diftype_t ;
struct TYPE_17__ {int dtdo_len; int dtdo_intlen; int dtdo_strlen; int dtdo_varlen; int dtdo_xlmlen; void* dtdo_rtype; int dtdo_krelen; int dtdo_urelen; TYPE_7__* dtdo_ureltab; TYPE_7__* dtdo_kreltab; TYPE_5__** dtdo_xlmtab; TYPE_7__* dtdo_vartab; TYPE_7__* dtdo_strtab; TYPE_7__* dtdo_inttab; TYPE_7__* dtdo_buf; } ;
typedef  TYPE_3__ dtrace_difo_t ;
struct TYPE_18__ {size_t dx_id; scalar_t__ dx_arg; } ;
typedef  TYPE_4__ dt_xlator_t ;
struct TYPE_19__ {int /*<<< orphan*/  dn_membid; TYPE_1__* dn_membexpr; } ;
typedef  TYPE_5__ dt_node_t ;
struct TYPE_20__ {TYPE_2__* ddo_pgp; int /*<<< orphan*/ * ddo_xlimport; } ;
typedef  TYPE_6__ dt_dof_t ;
typedef  int /*<<< orphan*/  dsecs ;
struct TYPE_21__ {void* dofr_tgtsec; void* dofr_relsec; void* dofr_strtab; int /*<<< orphan*/  dofd_links; int /*<<< orphan*/  dofd_rtype; scalar_t__ dofxr_argn; int /*<<< orphan*/  dofxr_member; int /*<<< orphan*/  dofxr_xlator; } ;
typedef  TYPE_7__ dof_xlref_t ;
typedef  void* dof_secidx_t ;
typedef  TYPE_7__ dof_relohdr_t ;
typedef  int /*<<< orphan*/  dof_relodesc_t ;
typedef  TYPE_7__ dof_difohdr_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_16__ {int /*<<< orphan*/ * dp_xrefs; } ;
struct TYPE_15__ {TYPE_4__* dn_xlator; } ;

/* Variables and functions */
 void* DOF_SECIDX_NONE ; 
 int /*<<< orphan*/  DOF_SECT_DIF ; 
 int /*<<< orphan*/  DOF_SECT_DIFOHDR ; 
 int /*<<< orphan*/  DOF_SECT_INTTAB ; 
 int /*<<< orphan*/  DOF_SECT_KRELHDR ; 
 int /*<<< orphan*/  DOF_SECT_RELTAB ; 
 int /*<<< orphan*/  DOF_SECT_STRTAB ; 
 int /*<<< orphan*/  DOF_SECT_URELHDR ; 
 int /*<<< orphan*/  DOF_SECT_VARTAB ; 
 int /*<<< orphan*/  DOF_SECT_XLTAB ; 
 TYPE_7__* alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (void**,int /*<<< orphan*/ *,int) ; 
 void* dof_add_lsect (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dt_popcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dof_secidx_t
dof_add_difo(dt_dof_t *ddo, const dtrace_difo_t *dp)
{
	dof_secidx_t dsecs[5]; /* enough for all possible DIFO sections */
	uint_t nsecs = 0;

	dof_difohdr_t *dofd;
	dof_relohdr_t dofr;
	dof_secidx_t relsec;

	dof_secidx_t strsec = DOF_SECIDX_NONE;
	dof_secidx_t intsec = DOF_SECIDX_NONE;
	dof_secidx_t hdrsec = DOF_SECIDX_NONE;

	if (dp->dtdo_buf != NULL) {
		dsecs[nsecs++] = dof_add_lsect(ddo, dp->dtdo_buf,
		    DOF_SECT_DIF, sizeof (dif_instr_t), 0,
		    sizeof (dif_instr_t), sizeof (dif_instr_t) * dp->dtdo_len);
	}

	if (dp->dtdo_inttab != NULL) {
		dsecs[nsecs++] = intsec = dof_add_lsect(ddo, dp->dtdo_inttab,
		    DOF_SECT_INTTAB, sizeof (uint64_t), 0,
		    sizeof (uint64_t), sizeof (uint64_t) * dp->dtdo_intlen);
	}

	if (dp->dtdo_strtab != NULL) {
		dsecs[nsecs++] = strsec = dof_add_lsect(ddo, dp->dtdo_strtab,
		    DOF_SECT_STRTAB, sizeof (char), 0, 0, dp->dtdo_strlen);
	}

	if (dp->dtdo_vartab != NULL) {
		dsecs[nsecs++] = dof_add_lsect(ddo, dp->dtdo_vartab,
		    DOF_SECT_VARTAB, sizeof (uint_t), 0, sizeof (dtrace_difv_t),
		    sizeof (dtrace_difv_t) * dp->dtdo_varlen);
	}

	if (dp->dtdo_xlmtab != NULL) {
		dof_xlref_t *xlt, *xlp;
		dt_node_t **pnp;

		xlt = alloca(sizeof (dof_xlref_t) * dp->dtdo_xlmlen);
		pnp = dp->dtdo_xlmtab;

		/*
		 * dtdo_xlmtab contains pointers to the translator members.
		 * The translator itself is in sect ddo_xlimport[dxp->dx_id].
		 * The XLMEMBERS entries are in order by their dn_membid, so
		 * the member section offset is the population count of bits
		 * in ddo_pgp->dp_xlrefs[] up to and not including dn_membid.
		 */
		for (xlp = xlt; xlp < xlt + dp->dtdo_xlmlen; xlp++) {
			dt_node_t *dnp = *pnp++;
			dt_xlator_t *dxp = dnp->dn_membexpr->dn_xlator;

			xlp->dofxr_xlator = ddo->ddo_xlimport[dxp->dx_id];
			xlp->dofxr_member = dt_popcb(
			    ddo->ddo_pgp->dp_xrefs[dxp->dx_id], dnp->dn_membid);
			xlp->dofxr_argn = (uint32_t)dxp->dx_arg;
		}

		dsecs[nsecs++] = dof_add_lsect(ddo, xlt, DOF_SECT_XLTAB,
		    sizeof (dof_secidx_t), 0, sizeof (dof_xlref_t),
		    sizeof (dof_xlref_t) * dp->dtdo_xlmlen);
	}

	/*
	 * Copy the return type and the array of section indices that form the
	 * DIFO into a single dof_difohdr_t and then add DOF_SECT_DIFOHDR.
	 */
	assert(nsecs <= sizeof (dsecs) / sizeof (dsecs[0]));
	dofd = alloca(sizeof (dtrace_diftype_t) + sizeof (dsecs));
	bcopy(&dp->dtdo_rtype, &dofd->dofd_rtype, sizeof (dtrace_diftype_t));
	bcopy(dsecs, &dofd->dofd_links, sizeof (dof_secidx_t) * nsecs);

	hdrsec = dof_add_lsect(ddo, dofd, DOF_SECT_DIFOHDR,
	    sizeof (dof_secidx_t), 0, 0,
	    sizeof (dtrace_diftype_t) + sizeof (dof_secidx_t) * nsecs);

	/*
	 * Add any other sections related to dtrace_difo_t.  These are not
	 * referenced in dof_difohdr_t because they are not used by emulation.
	 */
	if (dp->dtdo_kreltab != NULL) {
		relsec = dof_add_lsect(ddo, dp->dtdo_kreltab, DOF_SECT_RELTAB,
		    sizeof (uint64_t), 0, sizeof (dof_relodesc_t),
		    sizeof (dof_relodesc_t) * dp->dtdo_krelen);

		/*
		 * This code assumes the target of all relocations is the
		 * integer table 'intsec' (DOF_SECT_INTTAB).  If other sections
		 * need relocation in the future this will need to change.
		 */
		dofr.dofr_strtab = strsec;
		dofr.dofr_relsec = relsec;
		dofr.dofr_tgtsec = intsec;

		(void) dof_add_lsect(ddo, &dofr, DOF_SECT_KRELHDR,
		    sizeof (dof_secidx_t), 0, 0, sizeof (dof_relohdr_t));
	}

	if (dp->dtdo_ureltab != NULL) {
		relsec = dof_add_lsect(ddo, dp->dtdo_ureltab, DOF_SECT_RELTAB,
		    sizeof (uint64_t), 0, sizeof (dof_relodesc_t),
		    sizeof (dof_relodesc_t) * dp->dtdo_urelen);

		/*
		 * This code assumes the target of all relocations is the
		 * integer table 'intsec' (DOF_SECT_INTTAB).  If other sections
		 * need relocation in the future this will need to change.
		 */
		dofr.dofr_strtab = strsec;
		dofr.dofr_relsec = relsec;
		dofr.dofr_tgtsec = intsec;

		(void) dof_add_lsect(ddo, &dofr, DOF_SECT_URELHDR,
		    sizeof (dof_secidx_t), 0, 0, sizeof (dof_relohdr_t));
	}

	return (hdrsec);
}