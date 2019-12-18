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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_4__ {int m; int v; } ;
struct xfrm_state {int /*<<< orphan*/  tunnel_users; struct xfrm_state* tunnel; TYPE_3__ id; TYPE_2__ props; TYPE_1__ mark; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 struct xfrm_state* ipcomp6_tunnel_create (struct xfrm_state*) ; 
 scalar_t__ xfrm6_tunnel_spi_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_hold (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_insert (struct xfrm_state*) ; 
 struct xfrm_state* xfrm_state_lookup_with_mark (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipcomp6_tunnel_attach(struct xfrm_state *x)
{
	int err = 0;
	struct xfrm_state *t = NULL;
	__be32 spi;
	u32 mark = x->mark.m & x->mark.v;

	spi = xfrm6_tunnel_spi_lookup((xfrm_address_t *)&x->props.saddr);
	if (spi)
		t = xfrm_state_lookup_with_mark(&init_net, mark, (xfrm_address_t *)&x->id.daddr,
				      spi, IPPROTO_IPV6, AF_INET6);
	if (!t) {
		t = ipcomp6_tunnel_create(x);
		if (!t) {
			err = -EINVAL;
			goto out;
		}
		xfrm_state_insert(t);
		xfrm_state_hold(t);
	}
	x->tunnel = t;
	atomic_inc(&t->tunnel_users);

out:
	return err;
}