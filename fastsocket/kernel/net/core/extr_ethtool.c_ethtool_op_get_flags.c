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
typedef  int u32 ;
struct net_device {int features; } ;

/* Variables and functions */
 int flags_dup_features ; 

u32 ethtool_op_get_flags(struct net_device *dev)
{
	/* in the future, this function will probably contain additional
	 * handling for flags which are not so easily handled
	 * by a simple masking operation
	 */

	return dev->features & flags_dup_features;
}