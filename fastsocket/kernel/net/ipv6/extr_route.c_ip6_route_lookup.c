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
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* fib6_rule_lookup (struct net*,struct flowi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_pol_route_lookup ; 

struct dst_entry * ip6_route_lookup(struct net *net, struct flowi *fl,
				    int flags)
{
	return fib6_rule_lookup(net, fl, flags, ip6_pol_route_lookup);
}