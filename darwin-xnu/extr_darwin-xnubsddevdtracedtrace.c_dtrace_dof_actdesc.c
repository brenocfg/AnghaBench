#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
typedef  scalar_t__ dtrace_actkind_t ;
struct TYPE_15__ {struct TYPE_15__* dtad_next; int /*<<< orphan*/ * dtad_difo; } ;
typedef  TYPE_1__ dtrace_actdesc_t ;
struct TYPE_16__ {scalar_t__ dofs_type; scalar_t__ dofs_offset; int dofs_align; int dofs_size; int dofs_entsize; } ;
typedef  TYPE_2__ dof_sec_t ;
struct TYPE_17__ {scalar_t__ dofh_loadsz; } ;
typedef  TYPE_3__ dof_hdr_t ;
struct TYPE_18__ {scalar_t__ dofa_strtab; size_t dofa_arg; scalar_t__ dofa_difo; int /*<<< orphan*/  dofa_uarg; int /*<<< orphan*/  dofa_ntuple; scalar_t__ dofa_kind; } ;
typedef  TYPE_4__ dof_actdesc_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DOF_SECIDX_NONE ; 
 scalar_t__ DOF_SECT_ACTDESC ; 
 int /*<<< orphan*/  DOF_SECT_DIFOHDR ; 
 int /*<<< orphan*/  DOF_SECT_STRTAB ; 
 scalar_t__ DTRACEACT_DIFEXPR ; 
 scalar_t__ DTRACEACT_ISPRINTFLIKE (scalar_t__) ; 
 scalar_t__ DTRACEACT_PRINTA ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 TYPE_1__* dtrace_actdesc_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dtrace_actdesc_release (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dtrace_actions_max ; 
 int /*<<< orphan*/ * dtrace_dof_difo (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_dof_error (TYPE_3__*,char*) ; 
 TYPE_2__* dtrace_dof_sect (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_actdesc_t *
dtrace_dof_actdesc(dof_hdr_t *dof, dof_sec_t *sec, dtrace_vstate_t *vstate,
    cred_t *cr)
{
	dtrace_actdesc_t *act, *first = NULL, *last = NULL, *next;
	dof_actdesc_t *desc;
	dof_sec_t *difosec;
	size_t offs;
	uintptr_t daddr = (uintptr_t)dof;
	uint64_t arg;
	dtrace_actkind_t kind;

	if (sec->dofs_type != DOF_SECT_ACTDESC) {
		dtrace_dof_error(dof, "invalid action section");
		return (NULL);
	}

	if (sec->dofs_offset + sizeof (dof_actdesc_t) > dof->dofh_loadsz) {
		dtrace_dof_error(dof, "truncated action description");
		return (NULL);
	}

	if (sec->dofs_align != sizeof (uint64_t)) {
		dtrace_dof_error(dof, "bad alignment in action description");
		return (NULL);
	}

	if (sec->dofs_size < sec->dofs_entsize) {
		dtrace_dof_error(dof, "section entry size exceeds total size");
		return (NULL);
	}

	if (sec->dofs_entsize != sizeof (dof_actdesc_t)) {
		dtrace_dof_error(dof, "bad entry size in action description");
		return (NULL);
	}

	if (sec->dofs_size / sec->dofs_entsize > dtrace_actions_max) {
		dtrace_dof_error(dof, "actions exceed dtrace_actions_max");
		return (NULL);
	}

	for (offs = 0; offs < sec->dofs_size; offs += sec->dofs_entsize) {
		desc = (dof_actdesc_t *)(daddr +
		    (uintptr_t)sec->dofs_offset + offs);
		kind = (dtrace_actkind_t)desc->dofa_kind;

		if ((DTRACEACT_ISPRINTFLIKE(kind) &&
		    (kind != DTRACEACT_PRINTA || desc->dofa_strtab != DOF_SECIDX_NONE)) ||
		    (kind == DTRACEACT_DIFEXPR && desc->dofa_strtab != DOF_SECIDX_NONE))
		{
			dof_sec_t *strtab;
			char *str, *fmt;
			uint64_t i;

			/*
			 * The argument to these actions is an index into the
			 * DOF string table.  For printf()-like actions, this
			 * is the format string.  For print(), this is the
			 * CTF type of the expression result.
			 */
			if ((strtab = dtrace_dof_sect(dof,
			    DOF_SECT_STRTAB, desc->dofa_strtab)) == NULL)
				goto err;

			str = (char *)((uintptr_t)dof +
			    (uintptr_t)strtab->dofs_offset);

			for (i = desc->dofa_arg; i < strtab->dofs_size; i++) {
				if (str[i] == '\0')
					break;
			}

			if (i >= strtab->dofs_size) {
				dtrace_dof_error(dof, "bogus format string");
				goto err;
			}

			if (i == desc->dofa_arg) {
				dtrace_dof_error(dof, "empty format string");
				goto err;
			}

			i -= desc->dofa_arg;
			fmt = kmem_alloc(i + 1, KM_SLEEP);
			bcopy(&str[desc->dofa_arg], fmt, i + 1);
			arg = (uint64_t)(uintptr_t)fmt;
		} else {
			if (kind == DTRACEACT_PRINTA) {
				ASSERT(desc->dofa_strtab == DOF_SECIDX_NONE);
				arg = 0;
			} else {
				arg = desc->dofa_arg;
			}
		}

		act = dtrace_actdesc_create(kind, desc->dofa_ntuple,
		    desc->dofa_uarg, arg);

		if (last != NULL) {
			last->dtad_next = act;
		} else {
			first = act;
		}

		last = act;

		if (desc->dofa_difo == DOF_SECIDX_NONE)
			continue;

		if ((difosec = dtrace_dof_sect(dof,
		    DOF_SECT_DIFOHDR, desc->dofa_difo)) == NULL)
			goto err;

		act->dtad_difo = dtrace_dof_difo(dof, difosec, vstate, cr);

		if (act->dtad_difo == NULL)
			goto err;
	}

	ASSERT(first != NULL);
	return (first);

err:
	for (act = first; act != NULL; act = next) {
		next = act->dtad_next;
		dtrace_actdesc_release(act, vstate);
	}

	return (NULL);
}