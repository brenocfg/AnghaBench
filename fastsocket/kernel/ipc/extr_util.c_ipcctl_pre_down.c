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
struct kern_ipc_perm {scalar_t__ cuid; scalar_t__ uid; } ;
struct ipc_ids {int /*<<< orphan*/  rw_mutex; } ;
struct ipc64_perm {int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 struct kern_ipc_perm* ERR_PTR (int) ; 
 int IPC_SET ; 
 scalar_t__ IS_ERR (struct kern_ipc_perm*) ; 
 int PTR_ERR (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  audit_ipc_obj (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  audit_ipc_set_perm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_euid () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct kern_ipc_perm* ipc_lock_check (struct ipc_ids*,int) ; 
 int /*<<< orphan*/  ipc_unlock (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct kern_ipc_perm *ipcctl_pre_down(struct ipc_ids *ids, int id, int cmd,
				      struct ipc64_perm *perm, int extra_perm)
{
	struct kern_ipc_perm *ipcp;
	uid_t euid;
	int err;

	down_write(&ids->rw_mutex);
	ipcp = ipc_lock_check(ids, id);
	if (IS_ERR(ipcp)) {
		err = PTR_ERR(ipcp);
		goto out_up;
	}

	audit_ipc_obj(ipcp);
	if (cmd == IPC_SET)
		audit_ipc_set_perm(extra_perm, perm->uid,
					 perm->gid, perm->mode);

	euid = current_euid();
	if (euid == ipcp->cuid ||
	    euid == ipcp->uid  || capable(CAP_SYS_ADMIN))
		return ipcp;

	err = -EPERM;
	ipc_unlock(ipcp);
out_up:
	up_write(&ids->rw_mutex);
	return ERR_PTR(err);
}