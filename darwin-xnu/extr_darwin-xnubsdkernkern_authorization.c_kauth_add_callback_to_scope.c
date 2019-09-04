#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kauth_scope_t ;
typedef  TYPE_3__* kauth_listener_t ;
struct TYPE_8__ {int /*<<< orphan*/  kl_idata; int /*<<< orphan*/  kl_callback; } ;
struct TYPE_7__ {int /*<<< orphan*/  ks_flags; TYPE_1__* ks_listeners; } ;
struct TYPE_6__ {TYPE_3__* kll_listenerp; int /*<<< orphan*/  kll_idata; int /*<<< orphan*/  kll_callback; } ;

/* Variables and functions */
 int ENOSPC ; 
 int KAUTH_SCOPE_MAX_LISTENERS ; 
 int /*<<< orphan*/  KS_F_HAS_LISTENERS ; 

__attribute__((used)) static int kauth_add_callback_to_scope(kauth_scope_t sp, kauth_listener_t klp)
{
	int		i;

	for (i = 0; i < KAUTH_SCOPE_MAX_LISTENERS; i++) {
		if (sp->ks_listeners[i].kll_listenerp == NULL) {
			sp->ks_listeners[i].kll_callback = klp->kl_callback;
			sp->ks_listeners[i].kll_idata = klp->kl_idata;
			sp->ks_listeners[i].kll_listenerp = klp;
			sp->ks_flags |= KS_F_HAS_LISTENERS;
			return(0);
		}
	}
	return(ENOSPC);
}