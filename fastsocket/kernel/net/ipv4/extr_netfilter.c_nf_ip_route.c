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
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 int ip_route_output_key (int /*<<< orphan*/ *,struct rtable**,struct flowi*) ; 

__attribute__((used)) static int nf_ip_route(struct dst_entry **dst, struct flowi *fl)
{
	return ip_route_output_key(&init_net, (struct rtable **)dst, fl);
}