#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct proc {int dummy; } ;
struct iopolicysys_args {scalar_t__ cmd; int /*<<< orphan*/  arg; } ;
struct _iopol_param_t {int iop_iotype; int /*<<< orphan*/  iop_policy; int /*<<< orphan*/  iop_scope; } ;
typedef  int /*<<< orphan*/  iop_param ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EIDRM ; 
 int EINVAL ; 
 scalar_t__ IOPOL_CMD_GET ; 
#define  IOPOL_TYPE_DISK 130 
#define  IOPOL_TYPE_VFS_ATIME_UPDATES 129 
#define  IOPOL_TYPE_VFS_HFS_CASE_SENSITIVITY 128 
 int copyin (int /*<<< orphan*/ ,struct _iopol_param_t*,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iopolicysys_disk (struct proc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _iopol_param_t*) ; 
 int iopolicysys_vfs_atime_updates (struct proc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _iopol_param_t*) ; 
 int iopolicysys_vfs_hfs_case_sensitivity (struct proc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _iopol_param_t*) ; 

int
iopolicysys(struct proc *p, struct iopolicysys_args *uap, int32_t *retval)
{
	int     error = 0;
	struct _iopol_param_t iop_param;

	if ((error = copyin(uap->arg, &iop_param, sizeof(iop_param))) != 0)
		goto out;

	switch (iop_param.iop_iotype) {
		case IOPOL_TYPE_DISK:
			error = iopolicysys_disk(p, uap->cmd, iop_param.iop_scope, iop_param.iop_policy, &iop_param);
			if (error == EIDRM) {
				*retval = -2;
				error = 0;
			}
			if (error)
				goto out;
			break;
		case IOPOL_TYPE_VFS_HFS_CASE_SENSITIVITY:
			error = iopolicysys_vfs_hfs_case_sensitivity(p, uap->cmd, iop_param.iop_scope, iop_param.iop_policy, &iop_param);
			if (error)
				goto out;
			break;
		case IOPOL_TYPE_VFS_ATIME_UPDATES:
			error = iopolicysys_vfs_atime_updates(p, uap->cmd, iop_param.iop_scope, iop_param.iop_policy, &iop_param);
			if (error)
				goto out;
			break;
		default:
			error = EINVAL;
			goto out;
	}

	/* Individual iotype handlers are expected to update iop_param, if requested with a GET command */
	if (uap->cmd == IOPOL_CMD_GET) {
		error = copyout((caddr_t)&iop_param, uap->arg, sizeof(iop_param));
		if (error)
			goto out;
	}

out:
	return (error);
}