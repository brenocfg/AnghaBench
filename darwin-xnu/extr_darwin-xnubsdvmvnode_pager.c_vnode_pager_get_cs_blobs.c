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
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 void* ubc_get_cs_blobs (struct vnode*) ; 

kern_return_t
vnode_pager_get_cs_blobs(
	struct vnode	*vp,
	void		**blobs)
{
	*blobs = ubc_get_cs_blobs(vp);
	return KERN_SUCCESS;
}