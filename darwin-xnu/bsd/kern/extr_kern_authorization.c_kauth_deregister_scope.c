#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kauth_scope_t ;
struct TYPE_7__ {TYPE_1__* ks_listeners; } ;
struct TYPE_6__ {int /*<<< orphan*/ * kll_listenerp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_SCOPELOCK () ; 
 int /*<<< orphan*/  KAUTH_SCOPEUNLOCK () ; 
 int KAUTH_SCOPE_MAX_LISTENERS ; 
 int /*<<< orphan*/  M_KAUTH ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_dangling_listeners ; 
 int /*<<< orphan*/  kauth_scopes ; 
 int /*<<< orphan*/  kl_link ; 
 int /*<<< orphan*/  ks_link ; 

void
kauth_deregister_scope(kauth_scope_t scope)
{
	int		i;

	KAUTH_SCOPELOCK();

	TAILQ_REMOVE(&kauth_scopes, scope, ks_link);
	
	/* relocate listeners back to the waiting list */
	for (i = 0; i < KAUTH_SCOPE_MAX_LISTENERS; i++) {
		if (scope->ks_listeners[i].kll_listenerp != NULL) {
			TAILQ_INSERT_TAIL(&kauth_dangling_listeners, scope->ks_listeners[i].kll_listenerp, kl_link);
			scope->ks_listeners[i].kll_listenerp = NULL;
			/* 
			 * XXX - kauth_todo - WARNING, do not clear kll_callback or
			 * kll_idata here.  they are part of our scope unlisten race hack
			 */
		}
	}
	KAUTH_SCOPEUNLOCK();
	FREE(scope, M_KAUTH);
	
	return;
}