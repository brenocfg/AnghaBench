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
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EREMOTE ; 
 int __xfrm_lookup (struct net*,struct dst_entry**,struct flowi*,struct sock*,int) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 

int xfrm_lookup(struct net *net, struct dst_entry **dst_p, struct flowi *fl,
		struct sock *sk, int flags)
{
	int err = __xfrm_lookup(net, dst_p, fl, sk, flags);

	if (err == -EREMOTE) {
		dst_release(*dst_p);
		*dst_p = NULL;
		err = -EAGAIN;
	}

	return err;
}