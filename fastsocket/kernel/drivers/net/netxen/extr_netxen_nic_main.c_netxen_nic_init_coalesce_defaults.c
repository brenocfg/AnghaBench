#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_time_us; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_time_us; } ;
struct TYPE_6__ {TYPE_2__ data; } ;
struct TYPE_4__ {TYPE_3__ normal; int /*<<< orphan*/  flags; } ;
struct netxen_adapter {TYPE_1__ coal; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS ; 
 int /*<<< orphan*/  NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US ; 
 int /*<<< orphan*/  NETXEN_DEFAULT_INTR_COALESCE_TX_PACKETS ; 
 int /*<<< orphan*/  NETXEN_DEFAULT_INTR_COALESCE_TX_TIME_US ; 
 int /*<<< orphan*/  NETXEN_NIC_INTR_DEFAULT ; 

__attribute__((used)) static void
netxen_nic_init_coalesce_defaults(struct netxen_adapter *adapter)
{
	adapter->coal.flags = NETXEN_NIC_INTR_DEFAULT;
	adapter->coal.normal.data.rx_time_us =
		NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US;
	adapter->coal.normal.data.rx_packets =
		NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS;
	adapter->coal.normal.data.tx_time_us =
		NETXEN_DEFAULT_INTR_COALESCE_TX_TIME_US;
	adapter->coal.normal.data.tx_packets =
		NETXEN_DEFAULT_INTR_COALESCE_TX_PACKETS;
}