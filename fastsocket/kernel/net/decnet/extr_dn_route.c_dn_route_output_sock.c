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
struct sock {int dummy; } ;
struct flowi {scalar_t__ proto; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int MSG_TRYHARD ; 
 int /*<<< orphan*/  XFRM_LOOKUP_WAIT ; 
 int __dn_route_output_key (struct dst_entry**,struct flowi*,int) ; 
 int /*<<< orphan*/  init_net ; 
 int xfrm_lookup (int /*<<< orphan*/ *,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 

int dn_route_output_sock(struct dst_entry **pprt, struct flowi *fl, struct sock *sk, int flags)
{
	int err;

	err = __dn_route_output_key(pprt, fl, flags & MSG_TRYHARD);
	if (err == 0 && fl->proto) {
		err = xfrm_lookup(&init_net, pprt, fl, sk,
				 (flags & MSG_DONTWAIT) ? 0 : XFRM_LOOKUP_WAIT);
	}
	return err;
}