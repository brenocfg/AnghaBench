#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* hard_packet_limit; void* hard_byte_limit; void* soft_packet_limit; void* soft_byte_limit; } ;
struct TYPE_5__ {int /*<<< orphan*/  add_time; } ;
struct TYPE_4__ {int /*<<< orphan*/  all; } ;
struct xfrm_state {int /*<<< orphan*/  lock; int /*<<< orphan*/ * inner_mode_iaf; int /*<<< orphan*/ * inner_mode; scalar_t__ replay_maxdiff; scalar_t__ replay_maxage; TYPE_3__ lft; TYPE_2__ curlft; int /*<<< orphan*/  rtimer; int /*<<< orphan*/  timer; int /*<<< orphan*/  byspi; int /*<<< orphan*/  bysrc; int /*<<< orphan*/  bydst; TYPE_1__ km; int /*<<< orphan*/  tunnel_users; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  xs_net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* XFRM_INF ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 struct xfrm_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  xfrm_replay_timer_handler ; 
 int /*<<< orphan*/  xfrm_timer_handler ; 

struct xfrm_state *xfrm_state_alloc(struct net *net)
{
	struct xfrm_state *x;

	x = kzalloc(sizeof(struct xfrm_state), GFP_ATOMIC);

	if (x) {
		write_pnet(&x->xs_net, net);
		atomic_set(&x->refcnt, 1);
		atomic_set(&x->tunnel_users, 0);
		INIT_LIST_HEAD(&x->km.all);
		INIT_HLIST_NODE(&x->bydst);
		INIT_HLIST_NODE(&x->bysrc);
		INIT_HLIST_NODE(&x->byspi);
		setup_timer(&x->timer, xfrm_timer_handler, (unsigned long)x);
		setup_timer(&x->rtimer, xfrm_replay_timer_handler,
				(unsigned long)x);
		x->curlft.add_time = get_seconds();
		x->lft.soft_byte_limit = XFRM_INF;
		x->lft.soft_packet_limit = XFRM_INF;
		x->lft.hard_byte_limit = XFRM_INF;
		x->lft.hard_packet_limit = XFRM_INF;
		x->replay_maxage = 0;
		x->replay_maxdiff = 0;
		x->inner_mode = NULL;
		x->inner_mode_iaf = NULL;
		spin_lock_init(&x->lock);
	}
	return x;
}