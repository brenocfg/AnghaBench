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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ethtool_op_set_tso (struct net_device*,scalar_t__) ; 
 scalar_t__ no_tx_offload (struct net_device*) ; 

__attribute__((used)) static int sky2_set_tso(struct net_device *dev, u32 data)
{
	if (data && no_tx_offload(dev))
		return -EINVAL;

	return ethtool_op_set_tso(dev, data);
}