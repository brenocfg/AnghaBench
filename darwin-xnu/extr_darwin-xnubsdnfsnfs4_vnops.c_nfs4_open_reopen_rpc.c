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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfs_open_file {int dummy; } ;
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OPEN_NOCREATE ; 
 int nfs4_open_rpc_internal (struct nfs_open_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int
nfs4_open_reopen_rpc(
	struct nfs_open_file *nofp,
	thread_t thd,
	kauth_cred_t cred,
	struct componentname *cnp,
	vnode_t dvp,
	vnode_t *vpp,
	int share_access,
	int share_deny)
{
	return (nfs4_open_rpc_internal(nofp, NULL, thd, cred, cnp, NULL, dvp, vpp, NFS_OPEN_NOCREATE, share_access, share_deny));
}