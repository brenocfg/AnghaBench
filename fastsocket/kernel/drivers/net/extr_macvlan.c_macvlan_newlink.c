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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_forward_skb ; 
 int macvlan_common_newlink (struct net_device*,struct nlattr**,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx ; 

__attribute__((used)) static int macvlan_newlink(struct net_device *dev,
			   struct nlattr *tb[], struct nlattr *data[])
{
	return macvlan_common_newlink(dev, tb, data,
				      netif_rx,
				      dev_forward_skb);
}