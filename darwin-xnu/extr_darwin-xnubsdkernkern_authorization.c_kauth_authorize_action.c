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
typedef  TYPE_2__* kauth_scope_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_5__ {int (* ks_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ;int ks_flags; TYPE_1__* ks_listeners; int /*<<< orphan*/  ks_idata; } ;
struct TYPE_4__ {int (* kll_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ;int /*<<< orphan*/  kll_idata; int /*<<< orphan*/ * kll_listenerp; } ;

/* Variables and functions */
 int EPERM ; 
 int KAUTH_RESULT_ALLOW ; 
 int KAUTH_RESULT_DEFER ; 
 int KAUTH_RESULT_DENY ; 
 int KAUTH_SCOPE_MAX_LISTENERS ; 
 int KS_F_HAS_LISTENERS ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 

int
kauth_authorize_action(kauth_scope_t scope, kauth_cred_t credential, kauth_action_t action,
    uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3)
{
	int result, ret, i;

	/* ask the scope */
	if (scope->ks_callback != NULL)
		result = scope->ks_callback(credential, scope->ks_idata, action, arg0, arg1, arg2, arg3);
	else
		result = KAUTH_RESULT_DEFER;

	/* check with listeners */
	if ((scope->ks_flags & KS_F_HAS_LISTENERS) != 0) {
		for (i = 0; i < KAUTH_SCOPE_MAX_LISTENERS; i++) {
			/* XXX - kauth_todo - there is a race here if listener is removed - we will fix this post Tiger. 
			 * Until the race is fixed our kext clients are responsible for all active requests that may
			 * be in their callbacks or on the way to their callbacks before they free kl_callback or kl_idata.
			 * We keep copies of these in our kauth_local_listener in an attempt to limit our expose to 
			 * unlisten race. 
			 */
			if (scope->ks_listeners[i].kll_listenerp == NULL || 
				scope->ks_listeners[i].kll_callback == NULL) 
				continue;

			ret = scope->ks_listeners[i].kll_callback(
					credential, scope->ks_listeners[i].kll_idata, 
					action, arg0, arg1, arg2, arg3);
			if ((ret == KAUTH_RESULT_DENY) ||
				(result == KAUTH_RESULT_DEFER))
				result = ret;
		}
	}

	/* we need an explicit allow, or the auth fails */
 	/* XXX need a mechanism for auth failure to be signalled vs. denial */
 	return(result == KAUTH_RESULT_ALLOW ? 0 : EPERM);
}