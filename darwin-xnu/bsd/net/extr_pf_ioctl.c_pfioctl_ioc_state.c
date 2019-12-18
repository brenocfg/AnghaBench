#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct proc {int dummy; } ;
struct pfsync_state {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; int /*<<< orphan*/  ifname; int /*<<< orphan*/  timeout; } ;
struct pfioc_state {struct pfsync_state state; } ;
struct pfi_kif {int dummy; } ;
struct pf_state_key {TYPE_1__* state_key; int /*<<< orphan*/  unlink_hooks; } ;
struct pf_state_cmp {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
struct pf_state {TYPE_1__* state_key; int /*<<< orphan*/  unlink_hooks; } ;
struct TYPE_4__ {int /*<<< orphan*/  states; } ;
struct TYPE_3__ {int /*<<< orphan*/  app_state; } ;

/* Variables and functions */
#define  DIOCADDSTATE 129 
#define  DIOCGETSTATE 128 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PFI_KIF_REF_NONE ; 
 int /*<<< orphan*/  PFTM_MAX ; 
 int /*<<< orphan*/  PR_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct pf_state_key*,int) ; 
 struct pf_state_key* pf_alloc_state_key (struct pf_state_key*,int /*<<< orphan*/ *) ; 
 TYPE_2__ pf_default_rule ; 
 struct pf_state_key* pf_find_state_byid (struct pf_state_cmp*) ; 
 int /*<<< orphan*/  pf_insert_state (struct pfi_kif*,struct pf_state_key*) ; 
 int /*<<< orphan*/  pf_state_export (struct pfsync_state*,TYPE_1__*,struct pf_state_key*) ; 
 int /*<<< orphan*/  pf_state_import (struct pfsync_state*,struct pf_state_key*,struct pf_state_key*) ; 
 int /*<<< orphan*/  pf_state_key_pl ; 
 int /*<<< orphan*/  pf_state_pl ; 
 struct pfi_kif* pfi_kif_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_unref (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 struct pf_state_key* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_state_key*) ; 

__attribute__((used)) static int
pfioctl_ioc_state(u_long cmd, struct pfioc_state *ps, struct proc *p)
{
#pragma unused(p)
	int error = 0;

	switch (cmd) {
	case DIOCADDSTATE: {
		struct pfsync_state	*sp = &ps->state;
		struct pf_state		*s;
		struct pf_state_key	*sk;
		struct pfi_kif		*kif;

		if (sp->timeout >= PFTM_MAX) {
			error = EINVAL;
			break;
		}
		s = pool_get(&pf_state_pl, PR_WAITOK);
		if (s == NULL) {
			error = ENOMEM;
			break;
		}
		bzero(s, sizeof (struct pf_state));
		if ((sk = pf_alloc_state_key(s, NULL)) == NULL) {
			pool_put(&pf_state_pl, s);
			error = ENOMEM;
			break;
		}
		pf_state_import(sp, sk, s);
		kif = pfi_kif_get(sp->ifname);
		if (kif == NULL) {
			pool_put(&pf_state_pl, s);
			pool_put(&pf_state_key_pl, sk);
			error = ENOENT;
			break;
		}
		TAILQ_INIT(&s->unlink_hooks);
		s->state_key->app_state = 0;
		if (pf_insert_state(kif, s)) {
			pfi_kif_unref(kif, PFI_KIF_REF_NONE);
			pool_put(&pf_state_pl, s);
			error = EEXIST;
			break;
		}
		pf_default_rule.states++;
		VERIFY(pf_default_rule.states != 0);
		break;
	}

	case DIOCGETSTATE: {
		struct pf_state		*s;
		struct pf_state_cmp	 id_key;

		bcopy(ps->state.id, &id_key.id, sizeof (id_key.id));
		id_key.creatorid = ps->state.creatorid;

		s = pf_find_state_byid(&id_key);
		if (s == NULL) {
			error = ENOENT;
			break;
		}

		pf_state_export(&ps->state, s->state_key, s);
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}