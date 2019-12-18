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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;
struct nfs_open_file {int dummy; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int nfs4_open_rpc_internal (struct nfs_open_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*,struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_open_rpc(
	struct nfs_open_file *nofp,
	vfs_context_t ctx,
	struct componentname *cnp,
	struct vnode_attr *vap,
	vnode_t dvp,
	vnode_t *vpp,
	int create,
	int share_access,
	int share_deny)
{
	return (nfs4_open_rpc_internal(nofp, ctx, vfs_context_thread(ctx), vfs_context_ucred(ctx),
					cnp, vap, dvp, vpp, create, share_access, share_deny));
}