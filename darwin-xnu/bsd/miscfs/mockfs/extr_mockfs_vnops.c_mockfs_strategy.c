#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
struct vnop_strategy_args {int /*<<< orphan*/  a_bp; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int EIO ; 
 int buf_strategy (scalar_t__,struct vnop_strategy_args*) ; 
 TYPE_1__* buf_vnode (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_devvp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

int mockfs_strategy(struct vnop_strategy_args * ap)
{
	int rvalue;
	vnode_t dvp;

	/*
	 * We'll avoid checking for a memory-backed device here; we already do this for blockmap, which will be
	 *   called as part of the IO path.
	 */

	dvp = vfs_devvp(buf_vnode(ap->a_bp)->v_mount);

	if (dvp) {
		rvalue = buf_strategy(dvp, ap);
		vnode_put(dvp);
	}
	else {
		/*
		 * I'm not certain this is the BEST error to return for this case.
		 */
		rvalue = EIO;
	}

	return rvalue;
}