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
struct net {int dummy; } ;
struct arg_dev_net {struct net* net; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_clean_all (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arg_dev_net*) ; 
 int /*<<< orphan*/  fib6_ifdown ; 
 int /*<<< orphan*/  icmp6_clean_all (int /*<<< orphan*/ ,struct arg_dev_net*) ; 

void rt6_ifdown(struct net *net, struct net_device *dev)
{
	struct arg_dev_net adn = {
		.dev = dev,
		.net = net,
	};

	fib6_clean_all(net, fib6_ifdown, 0, &adn);
	icmp6_clean_all(fib6_ifdown, &adn);
}