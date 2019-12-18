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
struct TYPE_2__ {scalar_t__ interface_type; } ;
struct be_adapter {TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_SFP_PLUS_10GB ; 
 scalar_t__ PHY_TYPE_XFP_10GB ; 

bool be_pause_supported(struct be_adapter *adapter)
{
	return (adapter->phy.interface_type == PHY_TYPE_SFP_PLUS_10GB ||
		adapter->phy.interface_type == PHY_TYPE_XFP_10GB) ?
		false : true;
}