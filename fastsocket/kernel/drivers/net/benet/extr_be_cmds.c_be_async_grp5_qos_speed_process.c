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
struct be_async_event_grp5_qos_link_speed {scalar_t__ physical_port; int /*<<< orphan*/  qos_link_speed; } ;
struct TYPE_2__ {int link_speed; } ;
struct be_adapter {scalar_t__ port_num; TYPE_1__ phy; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_async_grp5_qos_speed_process(struct be_adapter *adapter,
		struct be_async_event_grp5_qos_link_speed *evt)
{
	if (adapter->phy.link_speed >= 0 &&
	    evt->physical_port == adapter->port_num)
		adapter->phy.link_speed = le16_to_cpu(evt->qos_link_speed) * 10;
}