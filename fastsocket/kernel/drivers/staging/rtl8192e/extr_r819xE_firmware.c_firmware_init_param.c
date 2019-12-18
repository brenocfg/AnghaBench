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
struct r8192_priv {TYPE_1__* pFirmware; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdpacket_frag_thresold; } ;
typedef  TYPE_1__ rt_firmware ;

/* Variables and functions */
 int /*<<< orphan*/  GET_COMMAND_PACKET_FRAG_THRESHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRANSMIT_BUFFER_SIZE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

void firmware_init_param(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	rt_firmware *pfirmware = priv->pFirmware;

	pfirmware->cmdpacket_frag_thresold =
		GET_COMMAND_PACKET_FRAG_THRESHOLD(MAX_TRANSMIT_BUFFER_SIZE);
}