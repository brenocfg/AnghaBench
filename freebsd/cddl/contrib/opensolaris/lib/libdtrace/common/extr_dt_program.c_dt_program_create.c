#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dp_dofversion; } ;
typedef  TYPE_1__ dtrace_prog_t ;
struct TYPE_10__ {int /*<<< orphan*/  dt_programs; } ;
typedef  TYPE_2__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOF_VERSION_1 ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  dt_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dt_zalloc (TYPE_2__*,int) ; 

dtrace_prog_t *
dt_program_create(dtrace_hdl_t *dtp)
{
	dtrace_prog_t *pgp = dt_zalloc(dtp, sizeof (dtrace_prog_t));

	if (pgp != NULL) {
		dt_list_append(&dtp->dt_programs, pgp);
	} else {
		(void) dt_set_errno(dtp, EDT_NOMEM);
		return (NULL);
	}

	/*
	 * By default, programs start with DOF version 1 so that output files
	 * containing DOF are backward compatible. If a program requires new
	 * DOF features, the version is increased as needed.
	 */
	pgp->dp_dofversion = DOF_VERSION_1;

	return (pgp);
}