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
struct net_device {int dummy; } ;
struct TYPE_2__ {unsigned int tx_chan; } ;

/* Variables and functions */
 TYPE_1__* netdev2pinfo (struct net_device const*) ; 

unsigned int cxgb4_port_chan(const struct net_device *dev)
{
	return netdev2pinfo(dev)->tx_chan;
}