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
struct vnop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/ * v_data; } ;
struct fdescnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct fdescnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct fdescnode* VTOFDESC (struct vnode*) ; 
 int /*<<< orphan*/  fd_hash ; 
 int /*<<< orphan*/  fdesc_lock () ; 
 int /*<<< orphan*/  fdesc_unlock () ; 

int
fdesc_reclaim(struct vnop_reclaim_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct fdescnode *fd = VTOFDESC(vp);

	fdesc_lock();

	LIST_REMOVE(fd, fd_hash);
	FREE(vp->v_data, M_TEMP);
	vp->v_data = NULL;
	
	fdesc_unlock();

	return (0);
}