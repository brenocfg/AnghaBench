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
struct flowi {int dummy; } ;
struct dst_entry {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 struct dst_entry* ip6_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi*) ; 

__attribute__((used)) static int nf_ip6_route(struct dst_entry **dst, struct flowi *fl)
{
	*dst = ip6_route_output(&init_net, NULL, fl);
	return (*dst)->error;
}