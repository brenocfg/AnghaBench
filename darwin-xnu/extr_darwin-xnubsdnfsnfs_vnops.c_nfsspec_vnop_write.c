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
struct vnop_write_args {int /*<<< orphan*/  a_vp; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {TYPE_1__ n_mtim; int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUPD ; 
 int VOCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnop_write_args*) ; 
 int /*<<< orphan*/  VOFFSET (int /*<<< orphan*/ ) ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  spec_vnodeop_p ; 
 int /*<<< orphan*/  vnop_write ; 

int
nfsspec_vnop_write(
	struct vnop_write_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		struct uio *a_uio;
		int a_ioflag;
		vfs_context_t a_context;
	} */ *ap)
{
	nfsnode_t np = VTONFS(ap->a_vp);
	struct timespec now;
	int error;

	/*
	 * Set update flag.
	 */
	if ((error = nfs_node_lock(np)))
		return (error);
	np->n_flag |= NUPD;
	nanotime(&now);
	np->n_mtim.tv_sec = now.tv_sec;
	np->n_mtim.tv_nsec = now.tv_nsec;
	nfs_node_unlock(np);
	return (VOCALL(spec_vnodeop_p, VOFFSET(vnop_write), ap));
}