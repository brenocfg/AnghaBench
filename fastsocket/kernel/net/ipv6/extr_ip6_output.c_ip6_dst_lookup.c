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
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int ip6_dst_lookup_tail (struct sock*,struct dst_entry**,struct flowi*) ; 

int ip6_dst_lookup(struct sock *sk, struct dst_entry **dst, struct flowi *fl)
{
	*dst = NULL;
	return ip6_dst_lookup_tail(sk, dst, fl);
}