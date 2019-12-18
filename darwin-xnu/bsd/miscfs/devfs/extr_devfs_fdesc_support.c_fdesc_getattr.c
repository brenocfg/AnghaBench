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
struct vnop_getattr_args {int /*<<< orphan*/  a_context; struct vnode_attr* a_vap; struct vnode* a_vp; } ;
struct vnode_attr {int /*<<< orphan*/  va_type; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;
struct TYPE_2__ {int fd_type; unsigned int fd_fd; } ;

/* Variables and functions */
#define  Fdesc 128 
 TYPE_1__* VTOFDESC (struct vnode*) ; 
 int fdesc_attr (unsigned int,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_setneedinactive (struct vnode*) ; 

int
fdesc_getattr(struct vnop_getattr_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode_attr *vap = ap->a_vap;
	unsigned fd;
	int error = 0;

	switch (VTOFDESC(vp)->fd_type) {
	case Fdesc:
		fd = VTOFDESC(vp)->fd_fd;
		error = fdesc_attr(fd, vap, ap->a_context);
		break;

	default:
		panic("Invalid type for an fdesc node!\n");
		break;	
	}
	
	/* 
	 * Yes, we do this without locking, but this value is always just
	 * a snapshot.
	 */
	if (error == 0) {
		vp->v_type = vap->va_type;
		
		/* We need an inactive to reset type to VNON */
		vnode_setneedinactive(vp);
	}

	return (error);
}