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
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  family; } ;
struct TYPE_8__ {int /*<<< orphan*/  proto; scalar_t__ spi; int /*<<< orphan*/  daddr; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_6__ {int v; int m; } ;
struct xfrm_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  byspi; TYPE_4__ props; TYPE_3__ id; TYPE_2__ km; TYPE_1__ mark; } ;
struct TYPE_10__ {scalar_t__ state_byspi; } ;
struct net {TYPE_5__ xfrm; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ htonl (int) ; 
 int net_random () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int xfrm_spi_hash (struct net*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_lock ; 
 struct xfrm_state* xfrm_state_lookup_with_mark (struct net*,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

int xfrm_alloc_spi(struct xfrm_state *x, u32 low, u32 high)
{
	struct net *net = xs_net(x);
	unsigned int h;
	struct xfrm_state *x0;
	int err = -ENOENT;
	__be32 minspi = htonl(low);
	__be32 maxspi = htonl(high);
	u32 mark = x->mark.v & x->mark.m;

	spin_lock_bh(&x->lock);
	if (x->km.state == XFRM_STATE_DEAD)
		goto unlock;

	err = 0;
	if (x->id.spi)
		goto unlock;

	err = -ENOENT;

	if (minspi == maxspi) {
		x0 = xfrm_state_lookup_with_mark(net, mark, &x->id.daddr, minspi, x->id.proto, x->props.family);
		if (x0) {
			xfrm_state_put(x0);
			goto unlock;
		}
		x->id.spi = minspi;
	} else {
		u32 spi = 0;
		for (h=0; h<high-low+1; h++) {
			spi = low + net_random()%(high-low+1);
			x0 = xfrm_state_lookup_with_mark(net, mark, &x->id.daddr, htonl(spi), x->id.proto, x->props.family);
			if (x0 == NULL) {
				x->id.spi = htonl(spi);
				break;
			}
			xfrm_state_put(x0);
		}
	}
	if (x->id.spi) {
		spin_lock_bh(&xfrm_state_lock);
		h = xfrm_spi_hash(net, &x->id.daddr, x->id.spi, x->id.proto, x->props.family);
		hlist_add_head(&x->byspi, net->xfrm.state_byspi+h);
		spin_unlock_bh(&xfrm_state_lock);

		err = 0;
	}

unlock:
	spin_unlock_bh(&x->lock);

	return err;
}