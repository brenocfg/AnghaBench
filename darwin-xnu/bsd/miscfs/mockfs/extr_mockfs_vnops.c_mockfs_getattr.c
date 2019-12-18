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
typedef  TYPE_1__* vnode_t ;
struct vnop_getattr_args {struct vnode_attr* a_vap; TYPE_1__* a_vp; } ;
struct vnode_attr {int dummy; } ;
typedef  TYPE_2__* mockfs_fsnode_t ;
struct TYPE_4__ {int type; int size; } ;
struct TYPE_3__ {scalar_t__ v_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 int /*<<< orphan*/  bzero (struct vnode_attr*,int) ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_nlink ; 
 int /*<<< orphan*/  va_total_alloc ; 
 int /*<<< orphan*/  va_total_size ; 

int mockfs_getattr(struct vnop_getattr_args * ap)
{
	/*
	 * For the moment, we don't actually care about most attributes.  We'll
	 *   deal with actually managing attributes as part of the general cleanup.
	 */
	vnode_t vp;
	mockfs_fsnode_t fsnode;
	struct vnode_attr * vap;

	vp = ap->a_vp;
	fsnode = (mockfs_fsnode_t)vp->v_data;
	vap = ap->a_vap;
	bzero(vap, sizeof(*vap));
	VATTR_RETURN(vap, va_nlink, 1); /* Simply assert that someone has at least one link to us */
	VATTR_RETURN(vap, va_mode, VREAD | VWRITE | VEXEC);
	VATTR_RETURN(vap, va_fileid, fsnode->type);
	VATTR_RETURN(vap, va_total_size, fsnode->size);
	VATTR_RETURN(vap, va_total_alloc, fsnode->size);
	VATTR_RETURN(vap, va_data_size, fsnode->size);
	VATTR_RETURN(vap, va_data_alloc, fsnode->size);

	return (0);
}