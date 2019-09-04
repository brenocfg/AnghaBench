#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_6__ {int /*<<< orphan*/  b_dev; } ;
struct TYPE_5__ {scalar_t__ v_type; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 

errno_t
buf_setdevice(buf_t bp, vnode_t vp) {

        if ((vp->v_type != VBLK) && (vp->v_type != VCHR))
	        return EINVAL;
	bp->b_dev = vp->v_rdev;

	return 0;
}