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
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int ip_route_output_flow (struct net*,struct rtable**,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ip_route_output_key(struct net *net, struct rtable **rp, struct flowi *flp)
{
	return ip_route_output_flow(net, rp, flp, NULL, 0);
}