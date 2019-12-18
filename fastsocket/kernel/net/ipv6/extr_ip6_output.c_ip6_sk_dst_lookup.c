#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_cookie; } ;

/* Variables and functions */
 TYPE_1__* inet6_sk (struct sock*) ; 
 int ip6_dst_lookup_tail (struct sock*,struct dst_entry**,struct flowi*) ; 
 struct dst_entry* ip6_sk_dst_check (struct sock*,struct dst_entry*,struct flowi*) ; 
 struct dst_entry* sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 

int ip6_sk_dst_lookup(struct sock *sk, struct dst_entry **dst, struct flowi *fl)
{
	*dst = NULL;
	if (sk) {
		*dst = sk_dst_check(sk, inet6_sk(sk)->dst_cookie);
		*dst = ip6_sk_dst_check(sk, *dst, fl);
	}

	return ip6_dst_lookup_tail(sk, dst, fl);
}