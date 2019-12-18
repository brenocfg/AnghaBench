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
struct vnop_symlink_args {int /*<<< orphan*/ * a_vpp; int /*<<< orphan*/  a_target; int /*<<< orphan*/  a_vap; int /*<<< orphan*/  a_cnp; int /*<<< orphan*/  a_dvp; int /*<<< orphan*/  a_context; } ;
typedef  int /*<<< orphan*/ * nfsnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFLNK ; 
 int /*<<< orphan*/  NFSTOV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VTONFS (int /*<<< orphan*/ ) ; 
 int nfs4_create_rpc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
nfs4_vnop_symlink(
	struct vnop_symlink_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_dvp;
		vnode_t *a_vpp;
		struct componentname *a_cnp;
		struct vnode_attr *a_vap;
		char *a_target;
		vfs_context_t a_context;
	} */ *ap)
{
	nfsnode_t np = NULL;
	int error;

	error = nfs4_create_rpc(ap->a_context, VTONFS(ap->a_dvp), ap->a_cnp, ap->a_vap,
			NFLNK, ap->a_target, &np);
	if (!error)
		*ap->a_vpp = NFSTOV(np);
	return (error);
}