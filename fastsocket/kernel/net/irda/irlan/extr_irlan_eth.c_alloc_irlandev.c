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
struct irlan_cb {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_netdev (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlan_eth_setup ; 

struct net_device *alloc_irlandev(const char *name)
{
	return alloc_netdev(sizeof(struct irlan_cb), name,
			    irlan_eth_setup);
}