#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {scalar_t__ dtc_difversion; scalar_t__ dtc_difintregs; scalar_t__ dtc_diftupregs; scalar_t__ dtc_ctfmodel; } ;
struct TYPE_9__ {TYPE_1__ dt_conf; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dof_sec_t ;
struct TYPE_10__ {scalar_t__* dofh_ident; int dofh_hdrsize; int dofh_secsize; int dofh_secoff; } ;
typedef  TYPE_3__ dof_hdr_t ;

/* Variables and functions */
 scalar_t__ CTF_MODEL_LP64 ; 
 scalar_t__ DOF_ENCODE_NATIVE ; 
 size_t DOF_ID_DIFIREG ; 
 size_t DOF_ID_DIFTREG ; 
 size_t DOF_ID_DIFVERS ; 
 size_t DOF_ID_ENCODING ; 
 size_t DOF_ID_MAG0 ; 
 size_t DOF_ID_MAG1 ; 
 size_t DOF_ID_MAG2 ; 
 size_t DOF_ID_MAG3 ; 
 size_t DOF_ID_MODEL ; 
 size_t DOF_ID_VERSION ; 
 scalar_t__ DOF_MAG_MAG0 ; 
 scalar_t__ DOF_MAG_MAG1 ; 
 scalar_t__ DOF_MAG_MAG2 ; 
 scalar_t__ DOF_MAG_MAG3 ; 
 scalar_t__ DOF_MODEL_ILP32 ; 
 scalar_t__ DOF_MODEL_LP64 ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ UINT8_MAX ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dof_hdr(dtrace_hdl_t *dtp, uint8_t dofversion, dof_hdr_t *hp)
{
	/*
	 * If our config values cannot fit in a uint8_t, we can't generate a
	 * DOF header since the values won't fit.  This can only happen if the
	 * user forcibly compiles a program with an artificial configuration.
	 */
	if (dtp->dt_conf.dtc_difversion > UINT8_MAX ||
	    dtp->dt_conf.dtc_difintregs > UINT8_MAX ||
	    dtp->dt_conf.dtc_diftupregs > UINT8_MAX)
		return (dt_set_errno(dtp, EOVERFLOW));

	bzero(hp, sizeof (dof_hdr_t));

	hp->dofh_ident[DOF_ID_MAG0] = DOF_MAG_MAG0;
	hp->dofh_ident[DOF_ID_MAG1] = DOF_MAG_MAG1;
	hp->dofh_ident[DOF_ID_MAG2] = DOF_MAG_MAG2;
	hp->dofh_ident[DOF_ID_MAG3] = DOF_MAG_MAG3;

	if (dtp->dt_conf.dtc_ctfmodel == CTF_MODEL_LP64)
		hp->dofh_ident[DOF_ID_MODEL] = DOF_MODEL_LP64;
	else
		hp->dofh_ident[DOF_ID_MODEL] = DOF_MODEL_ILP32;

	hp->dofh_ident[DOF_ID_ENCODING] = DOF_ENCODE_NATIVE;
	hp->dofh_ident[DOF_ID_VERSION] = dofversion;
	hp->dofh_ident[DOF_ID_DIFVERS] = dtp->dt_conf.dtc_difversion;
	hp->dofh_ident[DOF_ID_DIFIREG] = dtp->dt_conf.dtc_difintregs;
	hp->dofh_ident[DOF_ID_DIFTREG] = dtp->dt_conf.dtc_diftupregs;

	hp->dofh_hdrsize = sizeof (dof_hdr_t);
	hp->dofh_secsize = sizeof (dof_sec_t);
	hp->dofh_secoff = sizeof (dof_hdr_t);

	return (0);
}