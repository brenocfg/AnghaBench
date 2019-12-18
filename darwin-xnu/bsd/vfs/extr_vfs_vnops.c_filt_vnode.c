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
typedef  struct vnode* vnode_t ;
struct vnode {int dummy; } ;
struct knote {scalar_t__ kn_hook; } ;

/* Variables and functions */
 int filt_vnode_common (struct knote*,struct vnode*,long) ; 

__attribute__((used)) static int
filt_vnode(struct knote *kn, long hint)
{
	vnode_t vp = (struct vnode *)kn->kn_hook;

	return filt_vnode_common(kn, vp, hint);
}