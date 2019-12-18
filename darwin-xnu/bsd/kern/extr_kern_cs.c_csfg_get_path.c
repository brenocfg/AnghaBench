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
struct fileglob {scalar_t__ fg_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 int vn_getpath (struct vnode*,char*,int*) ; 

int
csfg_get_path(struct fileglob *fg, char *path, int *len)
{
	vnode_t vp = NULL;

	if (FILEGLOB_DTYPE(fg) != DTYPE_VNODE)
		return -1;
	
	vp = (struct vnode *)fg->fg_data;

	/* vn_getpath returns 0 for success,
	   or an error code */
	return vn_getpath(vp, path, len);
}