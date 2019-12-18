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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_filesec_t ;

/* Variables and functions */
 int KAUTH_VNODE_READ_ATTRIBUTES ; 
 int KAUTH_VNODE_READ_SECURITY ; 
 int /*<<< orphan*/  NOCRED ; 
 int mac_vnode_check_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*) ; 
 int vn_stat_noauth (struct vnode*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_authorize (struct vnode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
vn_stat(struct vnode *vp, void *sb, kauth_filesec_t *xsec, int isstat64, vfs_context_t ctx)
{
	int error;

#if CONFIG_MACF
	error = mac_vnode_check_stat(ctx, NOCRED, vp);
	if (error)
		return (error);
#endif

	/* authorize */
	if ((error = vnode_authorize(vp, NULL, KAUTH_VNODE_READ_ATTRIBUTES | KAUTH_VNODE_READ_SECURITY, ctx)) != 0)
		return(error);

	/* actual stat */
	return(vn_stat_noauth(vp, sb, xsec, isstat64, ctx, NOCRED));
}