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
typedef  int /*<<< orphan*/  uint32_t ;
struct proc {int p_vfs_iopolicy; } ;
struct _iopol_param_t {int iop_policy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FALSE ; 
#define  IOPOL_CMD_GET 132 
#define  IOPOL_CMD_SET 131 
#define  IOPOL_SCOPE_PROCESS 130 
#define  IOPOL_VFS_HFS_CASE_SENSITIVITY_DEFAULT 129 
#define  IOPOL_VFS_HFS_CASE_SENSITIVITY_FORCE_CASE_SENSITIVE 128 
 int /*<<< orphan*/  IOTaskHasEntitlement (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSBitAndAtomic16 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OSBitOrAtomic16 (int /*<<< orphan*/ ,int*) ; 
 int P_VFS_IOPOLICY_FORCE_HFS_CASE_SENSITIVITY ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iopolicysys_vfs_hfs_case_sensitivity(struct proc *p, int cmd, int scope, int policy, struct _iopol_param_t *iop_param)
{
	int			error = 0;

	/* Validate scope */
	switch (scope) {
		case IOPOL_SCOPE_PROCESS:
			/* Only process OK */
			break;
		default:
			error = EINVAL;
			goto out;
	}

	/* Validate policy */
	if (cmd == IOPOL_CMD_SET) {
		switch (policy) {
			case IOPOL_VFS_HFS_CASE_SENSITIVITY_DEFAULT:
				/* fall-through */
			case IOPOL_VFS_HFS_CASE_SENSITIVITY_FORCE_CASE_SENSITIVE:
				/* These policies are OK */
				break;
			default:
				error = EINVAL;
				goto out;
		}
	}

	/* Perform command */
	switch(cmd) {
		case IOPOL_CMD_SET:
			if (0 == kauth_cred_issuser(kauth_cred_get())) {
				/* If it's a non-root process, it needs to have the entitlement to set the policy */
				boolean_t entitled = FALSE;
				entitled = IOTaskHasEntitlement(current_task(), "com.apple.private.iopol.case_sensitivity");
				if (!entitled) {
					error = EPERM;
					goto out;
				}
			}

			switch (policy) {
				case IOPOL_VFS_HFS_CASE_SENSITIVITY_DEFAULT:
					OSBitAndAtomic16(~((uint32_t)P_VFS_IOPOLICY_FORCE_HFS_CASE_SENSITIVITY), &p->p_vfs_iopolicy);
					break;
				case IOPOL_VFS_HFS_CASE_SENSITIVITY_FORCE_CASE_SENSITIVE:
					OSBitOrAtomic16((uint32_t)P_VFS_IOPOLICY_FORCE_HFS_CASE_SENSITIVITY, &p->p_vfs_iopolicy);
					break;
				default:
					error = EINVAL;
					goto out;
			}
			
			break;
		case IOPOL_CMD_GET:
			iop_param->iop_policy = (p->p_vfs_iopolicy & P_VFS_IOPOLICY_FORCE_HFS_CASE_SENSITIVITY)
				? IOPOL_VFS_HFS_CASE_SENSITIVITY_FORCE_CASE_SENSITIVE
				: IOPOL_VFS_HFS_CASE_SENSITIVITY_DEFAULT;
			break;
		default:
			error = EINVAL; /* unknown command */
			break;
	}

out:
	return (error);
}