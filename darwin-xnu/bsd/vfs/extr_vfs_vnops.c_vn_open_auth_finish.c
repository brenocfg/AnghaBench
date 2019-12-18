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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_FILEOP_OPEN ; 
 int /*<<< orphan*/  kauth_authorize_fileop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vnode_notify_open (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_ref_ext (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vn_open_auth_finish(vnode_t vp, int fmode, vfs_context_t ctx)
{
	int error;

	if ((error = vnode_ref_ext(vp, fmode, 0)) != 0) {
		goto bad;
	}

	/* Call out to allow 3rd party notification of open. 
	 * Ignore result of kauth_authorize_fileop call.
	 */
#if CONFIG_MACF
	mac_vnode_notify_open(ctx, vp, fmode);
#endif
	kauth_authorize_fileop(vfs_context_ucred(ctx), KAUTH_FILEOP_OPEN, 
						   (uintptr_t)vp, 0);

	return 0;

bad:
	return error;

}