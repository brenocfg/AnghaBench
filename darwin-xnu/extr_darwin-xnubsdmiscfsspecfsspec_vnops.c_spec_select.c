#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnop_select_args {int /*<<< orphan*/  a_wql; int /*<<< orphan*/  a_which; TYPE_1__* a_vp; int /*<<< orphan*/  a_context; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int (* d_select ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int v_type; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
#define  VCHR 128 
 TYPE_2__* cdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

int
spec_select(struct vnop_select_args *ap)
{
	proc_t p = vfs_context_proc(ap->a_context);
	dev_t dev;

	switch (ap->a_vp->v_type) {

	default:
		return (1);		/* XXX */

	case VCHR:
		dev = ap->a_vp->v_rdev;
		return (*cdevsw[major(dev)].d_select)(dev, ap->a_which, ap->a_wql, p);
	}
}