#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u_long ;
struct proc {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_23__ {TYPE_7__ a; } ;
struct TYPE_24__ {TYPE_8__ v; } ;
struct TYPE_14__ {int /*<<< orphan*/  xport; TYPE_9__ addr; int /*<<< orphan*/  neg; } ;
struct TYPE_19__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_20__ {TYPE_4__ a; } ;
struct TYPE_21__ {TYPE_5__ v; } ;
struct TYPE_13__ {int /*<<< orphan*/  xport; TYPE_6__ addr; int /*<<< orphan*/  neg; } ;
struct pfioc_state_kill {char* psk_ifname; char* psk_ownername; int psk_af; TYPE_11__ psk_dst; int /*<<< orphan*/  psk_proto_variant; int /*<<< orphan*/  psk_proto; TYPE_10__ psk_src; } ;
struct pf_state_host {int /*<<< orphan*/  xport; int /*<<< orphan*/  addr; } ;
struct pf_state_key {int af_lan; int /*<<< orphan*/  proto; struct pf_state_host lan; struct pf_state_host ext_lan; int /*<<< orphan*/  direction; } ;
struct TYPE_18__ {TYPE_2__* ptr; } ;
struct pf_state {int /*<<< orphan*/  sync_flags; TYPE_3__ rule; TYPE_1__* kif; struct pf_state_key* state_key; } ;
struct TYPE_17__ {int /*<<< orphan*/  owner; } ;
struct TYPE_16__ {int /*<<< orphan*/  pfik_name; } ;
struct TYPE_15__ {int /*<<< orphan*/  hostid; } ;

/* Variables and functions */
#define  DIOCCLRSTATES 129 
#define  DIOCKILLSTATES 128 
 int /*<<< orphan*/  PFSTATE_NOSYNC ; 
 int /*<<< orphan*/  PF_MATCHA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PF_OUT ; 
 struct pf_state* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pf_state* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_state*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_match_xport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_state_tree_id ; 
 TYPE_12__ pf_status ; 
 int /*<<< orphan*/  pf_unlink_state (struct pf_state*) ; 
 int /*<<< orphan*/  pfsync_clear_states (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfsync_delete_state (struct pf_state*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_id ; 

__attribute__((used)) static int
pfioctl_ioc_state_kill(u_long cmd, struct pfioc_state_kill *psk, struct proc *p)
{
#pragma unused(p)
	int error = 0;

	psk->psk_ifname[sizeof (psk->psk_ifname) - 1] = '\0';
	psk->psk_ownername[sizeof(psk->psk_ownername) - 1] = '\0';

	bool ifname_matched = true;
	bool owner_matched = true;

	switch (cmd) {
	case DIOCCLRSTATES: {
		struct pf_state		*s, *nexts;
		int			 killed = 0;

		for (s = RB_MIN(pf_state_tree_id, &tree_id); s; s = nexts) {
			nexts = RB_NEXT(pf_state_tree_id, &tree_id, s);
			/*
			 * Purge all states only when neither ifname
			 * or owner is provided. If any of these are provided
			 * we purge only the states with meta data that match
			 */
			bool unlink_state = false;
			ifname_matched = true;
			owner_matched = true;

			if (psk->psk_ifname[0] &&
			    strcmp(psk->psk_ifname, s->kif->pfik_name)) {
				ifname_matched = false;
			}

			if (psk->psk_ownername[0] &&
			    ((NULL == s->rule.ptr) ||
			     strcmp(psk->psk_ownername, s->rule.ptr->owner))) {
				owner_matched = false;
			}

			unlink_state = ifname_matched && owner_matched;

			if (unlink_state) {
#if NPFSYNC
				/* don't send out individual delete messages */
				s->sync_flags = PFSTATE_NOSYNC;
#endif
				pf_unlink_state(s);
				killed++;
			}
		}
		psk->psk_af = killed;
#if NPFSYNC
		pfsync_clear_states(pf_status.hostid, psk->psk_ifname);
#endif
		break;
	}

	case DIOCKILLSTATES: {
		struct pf_state		*s, *nexts;
		struct pf_state_key	*sk;
		struct pf_state_host	*src, *dst;
		int			 killed = 0;

		for (s = RB_MIN(pf_state_tree_id, &tree_id); s;
		    s = nexts) {
			nexts = RB_NEXT(pf_state_tree_id, &tree_id, s);
			sk = s->state_key;
			ifname_matched = true;
			owner_matched = true;

			if (psk->psk_ifname[0] &&
			    strcmp(psk->psk_ifname, s->kif->pfik_name)) {
				ifname_matched = false;
			}

			if (psk->psk_ownername[0] &&
			    ((NULL == s->rule.ptr) ||
			     strcmp(psk->psk_ownername, s->rule.ptr->owner))) {
				owner_matched = false;
			}

			if (sk->direction == PF_OUT) {
				src = &sk->lan;
				dst = &sk->ext_lan;
			} else {
				src = &sk->ext_lan;
				dst = &sk->lan;
			}
			if ((!psk->psk_af || sk->af_lan == psk->psk_af) &&
			    (!psk->psk_proto || psk->psk_proto == sk->proto) &&
			    PF_MATCHA(psk->psk_src.neg,
			    &psk->psk_src.addr.v.a.addr,
			    &psk->psk_src.addr.v.a.mask,
			    &src->addr, sk->af_lan) &&
			    PF_MATCHA(psk->psk_dst.neg,
			    &psk->psk_dst.addr.v.a.addr,
			    &psk->psk_dst.addr.v.a.mask,
			    &dst->addr, sk->af_lan) &&
			    (pf_match_xport(psk->psk_proto,
			    psk->psk_proto_variant, &psk->psk_src.xport,
			    &src->xport)) &&
			    (pf_match_xport(psk->psk_proto,
			    psk->psk_proto_variant, &psk->psk_dst.xport,
			    &dst->xport)) &&
			    ifname_matched &&
			    owner_matched) {
#if NPFSYNC
				/* send immediate delete of state */
				pfsync_delete_state(s);
				s->sync_flags |= PFSTATE_NOSYNC;
#endif
				pf_unlink_state(s);
				killed++;
			}
		}
		psk->psk_af = killed;
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}