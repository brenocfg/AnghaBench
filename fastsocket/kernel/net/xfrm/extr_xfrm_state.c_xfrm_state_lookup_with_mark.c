#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct xfrm_state* __xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_lock ; 

struct xfrm_state *
xfrm_state_lookup_with_mark(struct net *net, u32 mark, xfrm_address_t *daddr, __be32 spi,
		  u8 proto, unsigned short family)
{
	struct xfrm_state *x;

	spin_lock_bh(&xfrm_state_lock);
	x = __xfrm_state_lookup(net, mark, daddr, spi, proto, family);
	spin_unlock_bh(&xfrm_state_lock);
	return x;
}