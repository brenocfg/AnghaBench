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
struct vnop_blktooff_args {void** a_offset; struct vnode* a_vp; } ;
struct vnode {int v_type; } ;
typedef  void* off_t ;

/* Variables and functions */
 int ENOTSUP ; 
#define  VBLK 129 
#define  VCHR 128 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
spec_blktooff(struct vnop_blktooff_args *ap)
{
	struct vnode *vp = ap->a_vp;

	switch (vp->v_type) {
	case VCHR:
		*ap->a_offset = (off_t)-1; /* failure */
		return (ENOTSUP);

	case VBLK:
		printf("spec_blktooff: not implemented for VBLK\n");
		*ap->a_offset = (off_t)-1; /* failure */
		return (ENOTSUP);

	default:
		panic("spec_blktooff type");
	}
	/* NOTREACHED */

	return (0);
}