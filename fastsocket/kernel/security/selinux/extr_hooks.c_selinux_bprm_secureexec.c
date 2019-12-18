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
typedef  scalar_t__ u32 ;
struct task_security_struct {scalar_t__ sid; scalar_t__ osid; } ;
struct linux_binprm {int dummy; } ;
struct cred {struct task_security_struct* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS__NOATSECURE ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cap_bprm_secureexec (struct linux_binprm*) ; 
 struct cred* current_cred () ; 

__attribute__((used)) static int selinux_bprm_secureexec(struct linux_binprm *bprm)
{
	const struct cred *cred = current_cred();
	const struct task_security_struct *tsec = cred->security;
	u32 sid, osid;
	int atsecure = 0;

	sid = tsec->sid;
	osid = tsec->osid;

	if (osid != sid) {
		/* Enable secure mode for SIDs transitions unless
		   the noatsecure permission is granted between
		   the two SIDs, i.e. ahp returns 0. */
		atsecure = avc_has_perm(osid, sid,
					SECCLASS_PROCESS,
					PROCESS__NOATSECURE, NULL);
	}

	return (atsecure || cap_bprm_secureexec(bprm));
}