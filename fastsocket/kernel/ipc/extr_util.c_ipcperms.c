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
typedef  scalar_t__ uid_t ;
struct kern_ipc_perm {int mode; scalar_t__ cuid; scalar_t__ uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  cgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_OWNER ; 
 int /*<<< orphan*/  audit_ipc_obj (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_euid () ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 int security_ipc_permission (struct kern_ipc_perm*,short) ; 

int ipcperms (struct kern_ipc_perm *ipcp, short flag)
{	/* flag will most probably be 0 or S_...UGO from <linux/stat.h> */
	uid_t euid = current_euid();
	int requested_mode, granted_mode;

	audit_ipc_obj(ipcp);
	requested_mode = (flag >> 6) | (flag >> 3) | flag;
	granted_mode = ipcp->mode;
	if (euid == ipcp->cuid ||
	    euid == ipcp->uid)
		granted_mode >>= 6;
	else if (in_group_p(ipcp->cgid) || in_group_p(ipcp->gid))
		granted_mode >>= 3;
	/* is there some bit set in requested_mode but not in granted_mode? */
	if ((requested_mode & ~granted_mode & 0007) && 
	    !capable(CAP_IPC_OWNER))
		return -1;

	return security_ipc_permission(ipcp, flag);
}