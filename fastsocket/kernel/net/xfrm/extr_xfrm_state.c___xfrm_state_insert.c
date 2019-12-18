#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * next; } ;
struct TYPE_8__ {int /*<<< orphan*/  family; int /*<<< orphan*/  saddr; int /*<<< orphan*/  reqid; } ;
struct TYPE_7__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  all; } ;
struct xfrm_state {TYPE_5__ bydst; scalar_t__ replay_maxage; int /*<<< orphan*/  rtimer; int /*<<< orphan*/  timer; TYPE_5__ byspi; TYPE_3__ props; TYPE_2__ id; TYPE_5__ bysrc; TYPE_1__ km; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_num; int /*<<< orphan*/  km_waitq; scalar_t__ state_byspi; scalar_t__ state_bysrc; scalar_t__ state_bydst; int /*<<< orphan*/  state_all; } ;
struct net {TYPE_4__ xfrm; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  hlist_add_head (TYPE_5__*,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 unsigned int xfrm_dst_hash (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_hash_grow_check (struct net*,int /*<<< orphan*/ ) ; 
 unsigned int xfrm_spi_hash (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int xfrm_src_hash (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void __xfrm_state_insert(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	unsigned int h;

	list_add(&x->km.all, &net->xfrm.state_all);

	h = xfrm_dst_hash(net, &x->id.daddr, &x->props.saddr,
			  x->props.reqid, x->props.family);
	hlist_add_head(&x->bydst, net->xfrm.state_bydst+h);

	h = xfrm_src_hash(net, &x->id.daddr, &x->props.saddr, x->props.family);
	hlist_add_head(&x->bysrc, net->xfrm.state_bysrc+h);

	if (x->id.spi) {
		h = xfrm_spi_hash(net, &x->id.daddr, x->id.spi, x->id.proto,
				  x->props.family);

		hlist_add_head(&x->byspi, net->xfrm.state_byspi+h);
	}

	mod_timer(&x->timer, jiffies + HZ);
	if (x->replay_maxage)
		mod_timer(&x->rtimer, jiffies + x->replay_maxage);

	wake_up(&net->xfrm.km_waitq);

	net->xfrm.state_num++;

	xfrm_hash_grow_check(net, x->bydst.next != NULL);
}