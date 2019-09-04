#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  scalar_t__ kauth_cred_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_3__ {scalar_t__ v_cred; int /*<<< orphan*/  v_authorized_actions; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (scalar_t__) ; 
 int /*<<< orphan*/  KAUTH_INVALIDATE_CACHED_RIGHTS ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  kauth_cred_unref (scalar_t__*) ; 

void vnode_uncache_authorized_action(vnode_t vp, kauth_action_t action)
{
        kauth_cred_t tcred = NOCRED;

	NAME_CACHE_LOCK();

	vp->v_authorized_actions &= ~action;

	if (action == KAUTH_INVALIDATE_CACHED_RIGHTS &&
	    IS_VALID_CRED(vp->v_cred)) {
	        /*
		 * Use a temp variable to avoid kauth_cred_unref() while NAME_CACHE_LOCK is held
		 */
	        tcred = vp->v_cred;
		vp->v_cred = NOCRED;
	}
	NAME_CACHE_UNLOCK();

	if (tcred != NOCRED)
		kauth_cred_unref(&tcred);
}