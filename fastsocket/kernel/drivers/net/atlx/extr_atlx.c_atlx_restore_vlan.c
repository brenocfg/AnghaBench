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
struct atlx_adapter {int /*<<< orphan*/  vlgrp; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atlx_vlan_rx_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atlx_restore_vlan(struct atlx_adapter *adapter)
{
	atlx_vlan_rx_register(adapter->netdev, adapter->vlgrp);
}