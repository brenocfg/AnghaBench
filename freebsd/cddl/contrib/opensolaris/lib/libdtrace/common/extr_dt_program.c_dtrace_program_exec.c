#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dpi_matches; } ;
typedef  TYPE_1__ dtrace_proginfo_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_7__ {scalar_t__ n_matched; void* dof; } ;
typedef  TYPE_2__ dtrace_enable_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEIOC_ENABLE ; 
 int /*<<< orphan*/  DTRACE_D_STRIP ; 
#define  E2BIG 131 
#define  EBUSY 130 
 int EDT_DIFFAULT ; 
 int EDT_DIFINVAL ; 
 int EDT_DIFSIZE ; 
 int EDT_ENABLING_ERR ; 
#define  EFAULT 129 
#define  EINVAL 128 
 int dt_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int) ; 
 void* dtrace_dof_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_dof_destroy (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dtrace_program_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int errno ; 

int
dtrace_program_exec(dtrace_hdl_t *dtp, dtrace_prog_t *pgp,
    dtrace_proginfo_t *pip)
{
	dtrace_enable_io_t args;
	void *dof;
	int n, err;

	dtrace_program_info(dtp, pgp, pip);

	if ((dof = dtrace_dof_create(dtp, pgp, DTRACE_D_STRIP)) == NULL)
		return (-1);

	args.dof = dof;
	args.n_matched = 0;
	n = dt_ioctl(dtp, DTRACEIOC_ENABLE, &args);
	dtrace_dof_destroy(dtp, dof);

	if (n == -1) {
		switch (errno) {
		case EINVAL:
			err = EDT_DIFINVAL;
			break;
		case EFAULT:
			err = EDT_DIFFAULT;
			break;
		case E2BIG:
			err = EDT_DIFSIZE;
			break;
		case EBUSY:
			err = EDT_ENABLING_ERR;
			break;
		default:
			err = errno;
		}

		return (dt_set_errno(dtp, err));
	}

	if (pip != NULL)
		pip->dpi_matches += args.n_matched;

	return (0);
}