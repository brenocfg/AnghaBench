#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ kauth_cred_t ;
typedef  scalar_t__ kauth_action_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {scalar_t__ v_type; scalar_t__ v_cred; scalar_t__ v_authorized_actions; int /*<<< orphan*/  v_cred_timestamp; TYPE_1__* v_mount; } ;
struct TYPE_4__ {int mnt_kern_flag; scalar_t__ mnt_authcache_ttl; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IS_VALID_CRED (scalar_t__) ; 
 scalar_t__ KAUTH_VNODE_SEARCH ; 
 int MNTK_AUTH_CACHE_TTL ; 
 int MNTK_AUTH_OPAQUE ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 scalar_t__ NOCRED ; 
 scalar_t__ TRUE ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  kauth_cred_ref (scalar_t__) ; 
 int /*<<< orphan*/  kauth_cred_unref (scalar_t__*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ vfs_context_ucred (int /*<<< orphan*/ ) ; 

void vnode_cache_authorized_action(vnode_t vp, vfs_context_t ctx, kauth_action_t action)
{
	kauth_cred_t tcred = NOCRED;
	kauth_cred_t ucred;
	struct timeval tv;
	boolean_t ttl_active = FALSE;

	ucred = vfs_context_ucred(ctx);

	if (!IS_VALID_CRED(ucred) || action == 0)
	        return;

	if ( (vp->v_mount->mnt_kern_flag & (MNTK_AUTH_OPAQUE | MNTK_AUTH_CACHE_TTL)) ) {
	        /*
		 * a TTL is enabled on the rights cache... handle it here
		 * a TTL of 0 indicates that no rights should be cached
		 */
	        if (vp->v_mount->mnt_authcache_ttl == 0) 
		        return;

		if ( !(vp->v_mount->mnt_kern_flag & MNTK_AUTH_CACHE_TTL) ) {
		        /*
			 * only cache SEARCH action for filesystems marked
			 * MNTK_AUTH_OPAQUE on VDIRs...
			 * the lookup_path code will time these out
			 */
		        if ( (action & ~KAUTH_VNODE_SEARCH) || vp->v_type != VDIR )
			        return;
		}
		ttl_active = TRUE;

		microuptime(&tv);
	}
	NAME_CACHE_LOCK();

	if (vp->v_cred != ucred) {
	        kauth_cred_ref(ucred);
	        /*
		 * Use a temp variable to avoid kauth_cred_unref() while NAME_CACHE_LOCK is held
		 */
		tcred = vp->v_cred;
		vp->v_cred = ucred;
		vp->v_authorized_actions = 0;
	}
	if (ttl_active == TRUE && vp->v_authorized_actions == 0) {
	        /*
		 * only reset the timestamnp on the
		 * first authorization cached after the previous
		 * timer has expired or we're switching creds...
		 * 'vnode_cache_is_authorized' will clear the 
		 * authorized actions if the TTL is active and
		 * it has expired
		 */
	        vp->v_cred_timestamp = tv.tv_sec;
	}
	vp->v_authorized_actions |= action;

	NAME_CACHE_UNLOCK();

	if (IS_VALID_CRED(tcred))
		kauth_cred_unref(&tcred);
}