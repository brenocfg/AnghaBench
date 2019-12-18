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
struct TYPE_2__ {int /*<<< orphan*/  fib6_main_tbl; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;
typedef  scalar_t__ (* pol_lookup_t ) (struct net*,int /*<<< orphan*/ ,struct flowi*,int) ;

/* Variables and functions */

struct dst_entry *fib6_rule_lookup(struct net *net, struct flowi *fl,
				   int flags, pol_lookup_t lookup)
{
	return (struct dst_entry *) lookup(net, net->ipv6.fib6_main_tbl, fl, flags);
}