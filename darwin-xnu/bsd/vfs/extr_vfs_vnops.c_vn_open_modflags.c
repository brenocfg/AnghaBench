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
struct vnode_attr {int dummy; } ;
struct nameidata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  va_mode ; 
 int vn_open_auth (struct nameidata*,int*,struct vnode_attr*) ; 

int
vn_open_modflags(struct nameidata *ndp, int *fmodep, int cmode)
{
	struct vnode_attr va;

	VATTR_INIT(&va);
	VATTR_SET(&va, va_mode, cmode);
	
	return(vn_open_auth(ndp, fmodep, &va));
}