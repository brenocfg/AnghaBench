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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __in6_dev_get (struct net_device const*) ; 
 size_t inet6_ifla6_size () ; 

__attribute__((used)) static size_t inet6_get_link_af_size(const struct net_device *dev)
{
	if (!__in6_dev_get(dev))
		return 0;

	return inet6_ifla6_size();
}