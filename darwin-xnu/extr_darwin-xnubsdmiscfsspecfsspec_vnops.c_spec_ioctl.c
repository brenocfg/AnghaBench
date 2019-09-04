#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vnop_ioctl_args {int /*<<< orphan*/  a_fflag; int /*<<< orphan*/  a_command; scalar_t__ a_data; TYPE_1__* a_vp; int /*<<< orphan*/  a_context; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {int (* d_ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int (* d_ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int v_type; int /*<<< orphan*/  v_specsize; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_IOCTL ; 
 int /*<<< orphan*/  DKIOCSETBLOCKSIZE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  VBLK 129 
#define  VCHR 128 
 TYPE_3__* bdevsw ; 
 TYPE_2__* cdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

int
spec_ioctl(struct vnop_ioctl_args *ap)
{
	proc_t p = vfs_context_proc(ap->a_context);
	dev_t dev = ap->a_vp->v_rdev;
	int	retval = 0;

	KERNEL_DEBUG_CONSTANT(FSDBG_CODE(DBG_IOCTL, 0) | DBG_FUNC_START,
		dev, ap->a_command, ap->a_fflag, ap->a_vp->v_type, 0);

	switch (ap->a_vp->v_type) {

	case VCHR:
		retval = (*cdevsw[major(dev)].d_ioctl)(dev, ap->a_command, ap->a_data,
						       ap->a_fflag, p);
		break;

	case VBLK:
		retval = (*bdevsw[major(dev)].d_ioctl)(dev, ap->a_command, ap->a_data, ap->a_fflag, p);
		if (!retval && ap->a_command == DKIOCSETBLOCKSIZE)
			ap->a_vp->v_specsize = *(uint32_t *)ap->a_data;
		break;

	default:
		panic("spec_ioctl");
		/* NOTREACHED */
	}
	KERNEL_DEBUG_CONSTANT(FSDBG_CODE(DBG_IOCTL, 0) | DBG_FUNC_END,
		dev, ap->a_command, ap->a_fflag, retval, 0);

	return (retval);
}