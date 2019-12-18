#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ n_matched; void* dof; } ;
struct TYPE_12__ {int dt_active; int dt_errno; TYPE_2__ dt_beganon; int /*<<< orphan*/ * dt_vector; int /*<<< orphan*/ * dt_errprog; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dtrace_enable_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEIOC_ENABLE ; 
 int /*<<< orphan*/  DTRACEIOC_GO ; 
 int E2BIG ; 
 int EACCES ; 
 int EALREADY ; 
 int EDT_BUFTOOSMALL ; 
 int EDT_DESTRUCTIVE ; 
 int EDT_ENDTOOBIG ; 
 int EDT_ISANON ; 
 int EDT_NOANON ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOTTY ; 
 int dt_aggregate_go (TYPE_1__*) ; 
 int dt_ioctl (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int dt_options_load (TYPE_1__*) ; 
 int dt_set_errno (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dtrace_dof_destroy (TYPE_1__*,void*) ; 
 void* dtrace_getopt_dof (TYPE_1__*) ; 
 int dtrace_program_exec (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int errno ; 

int
dtrace_go(dtrace_hdl_t *dtp)
{
	dtrace_enable_io_t args;
	void *dof;
	int error, r;

	if (dtp->dt_active)
		return (dt_set_errno(dtp, EINVAL));

	/*
	 * If a dtrace:::ERROR program and callback are registered, enable the
	 * program before we start tracing.  If this fails for a vector open
	 * with ENOTTY, we permit dtrace_go() to succeed so that vector clients
	 * such as mdb's dtrace module can execute the rest of dtrace_go() even
	 * though they do not provide support for the DTRACEIOC_ENABLE ioctl.
	 */
	if (dtp->dt_errprog != NULL &&
	    dtrace_program_exec(dtp, dtp->dt_errprog, NULL) == -1 && (
	    dtp->dt_errno != ENOTTY || dtp->dt_vector == NULL))
		return (-1); /* dt_errno has been set for us */

	if ((dof = dtrace_getopt_dof(dtp)) == NULL)
		return (-1); /* dt_errno has been set for us */

	args.dof = dof;
	args.n_matched = 0;
	r = dt_ioctl(dtp, DTRACEIOC_ENABLE, &args);
	error = errno;
	dtrace_dof_destroy(dtp, dof);

	if (r == -1 && (error != ENOTTY || dtp->dt_vector == NULL))
		return (dt_set_errno(dtp, error));

	if (dt_ioctl(dtp, DTRACEIOC_GO, &dtp->dt_beganon) == -1) {
		if (errno == EACCES)
			return (dt_set_errno(dtp, EDT_DESTRUCTIVE));

		if (errno == EALREADY)
			return (dt_set_errno(dtp, EDT_ISANON));

		if (errno == ENOENT)
			return (dt_set_errno(dtp, EDT_NOANON));

		if (errno == E2BIG)
			return (dt_set_errno(dtp, EDT_ENDTOOBIG));

		if (errno == ENOSPC)
			return (dt_set_errno(dtp, EDT_BUFTOOSMALL));

		return (dt_set_errno(dtp, errno));
	}

	dtp->dt_active = 1;

	if (dt_options_load(dtp) == -1)
		return (dt_set_errno(dtp, errno));

	return (dt_aggregate_go(dtp));
}