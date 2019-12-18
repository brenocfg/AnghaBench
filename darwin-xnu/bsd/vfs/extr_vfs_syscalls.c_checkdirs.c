#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct cdirargs {TYPE_1__* newdp; TYPE_1__* olddp; } ;
struct TYPE_8__ {int v_usecount; int /*<<< orphan*/  v_mountedhere; } ;

/* Variables and functions */
 int PROC_ALLPROCLIST ; 
 int PROC_NOWAITTRANS ; 
 int VFS_ROOT (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkdirs_callback ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  proc_iterate (int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* rootvnode ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_rele (TYPE_1__*) ; 

__attribute__((used)) static int
checkdirs(vnode_t olddp, vfs_context_t ctx)
{
	vnode_t newdp;
	vnode_t tvp;
	int err;
	struct cdirargs cdr;

	if (olddp->v_usecount == 1)
		return(0);
	err = VFS_ROOT(olddp->v_mountedhere, &newdp, ctx);

	if (err != 0) {
#if DIAGNOSTIC
		panic("mount: lost mount: error %d", err);
#endif
		return(err);
	}

	cdr.olddp = olddp;
	cdr.newdp = newdp;
	/* do not block for exec/fork trans as the vp in cwd & rootdir are not changing */
	proc_iterate(PROC_ALLPROCLIST | PROC_NOWAITTRANS, checkdirs_callback, (void *)&cdr, NULL, NULL);

	if (rootvnode == olddp) {
		vnode_ref(newdp);
		tvp = rootvnode;
		rootvnode = newdp;
		vnode_rele(tvp);
	}

	vnode_put(newdp);
	return(0);
}