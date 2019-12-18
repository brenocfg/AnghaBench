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
struct rt6_info {int /*<<< orphan*/  rt6i_dev; } ;
struct nl_info {int /*<<< orphan*/  nl_net; } ;

/* Variables and functions */
 int __ip6_del_rt (struct rt6_info*,struct nl_info*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 

int ip6_del_rt(struct rt6_info *rt)
{
	struct nl_info info = {
		.nl_net = dev_net(rt->rt6i_dev),
	};
	return __ip6_del_rt(rt, &info);
}