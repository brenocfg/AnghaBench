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
typedef  int /*<<< orphan*/  u8 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int Length; scalar_t__ Value; int /*<<< orphan*/  Op; } ;
typedef  TYPE_1__ DCMD_TXCMD_T ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_PACKET_TYPE_INIT ; 
 int /*<<< orphan*/  DRIVER_RSSI ; 
 int /*<<< orphan*/  TXCMD_SET_RX_RSSI ; 
 int /*<<< orphan*/  cmpk_message_handle_tx (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_send_rssi_tofw(struct net_device *dev)
{
	DCMD_TXCMD_T			tx_cmd;
	struct r8192_priv *priv = ieee80211_priv(dev);

	// If we test chariot, we should stop the TX command ?
	// Because 92E will always silent reset when we send tx command. We use register
	// 0x1e0(byte) to botify driver.
	write_nic_byte(dev, DRIVER_RSSI, (u8)priv->undecorated_smoothed_pwdb);
	return;
#if 1
	tx_cmd.Op		= TXCMD_SET_RX_RSSI;
	tx_cmd.Length	= 4;
	tx_cmd.Value		= priv->undecorated_smoothed_pwdb;

	cmpk_message_handle_tx(dev, (u8*)&tx_cmd,
								DESC_PACKET_TYPE_INIT, sizeof(DCMD_TXCMD_T));
#endif
}