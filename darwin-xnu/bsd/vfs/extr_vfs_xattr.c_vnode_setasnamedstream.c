#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {TYPE_1__* v_mount; } ;
struct TYPE_7__ {int mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MNTK_NAMED_STREAMS ; 
 int /*<<< orphan*/  vnode_setasnamedstream_internal (TYPE_2__*,TYPE_2__*) ; 

errno_t
vnode_setasnamedstream(vnode_t vp, vnode_t svp)
{
	if ((vp->v_mount->mnt_kern_flag & MNTK_NAMED_STREAMS) == 0)
		return (EINVAL);

	vnode_setasnamedstream_internal(vp, svp);
	return (0);
}