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
struct fileglob {scalar_t__ fg_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int EFTYPE ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 int mac_vnop_getxattr (struct vnode*,char const*,char*,size_t,size_t*) ; 

int
mac_file_getxattr(struct fileglob *fg, const char *name, char *buf, size_t len,
		size_t *attrlen) {
	struct vnode *vp = NULL;

	if (!fg || FILEGLOB_DTYPE(fg) != DTYPE_VNODE) {
		return EFTYPE;
	}

	vp = (struct vnode *)fg->fg_data;
	return mac_vnop_getxattr(vp, name, buf, len, attrlen);
}