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
struct ethtool_cmd {int speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  port; int /*<<< orphan*/  advertising; scalar_t__ phy_address; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  supported; } ;
struct de_private {int media_type; scalar_t__ media_lock; int /*<<< orphan*/  media_advertise; int /*<<< orphan*/  media_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
#define  DE_MEDIA_AUI 129 
#define  DE_MEDIA_BNC 128 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int FullDuplex ; 
 int /*<<< orphan*/  MacMode ; 
 int /*<<< orphan*/  PORT_AUI ; 
 int /*<<< orphan*/  PORT_BNC ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SPEED_10 ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int dr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __de_get_settings(struct de_private *de, struct ethtool_cmd *ecmd)
{
	ecmd->supported = de->media_supported;
	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->phy_address = 0;
	ecmd->advertising = de->media_advertise;

	switch (de->media_type) {
	case DE_MEDIA_AUI:
		ecmd->port = PORT_AUI;
		ecmd->speed = 5;
		break;
	case DE_MEDIA_BNC:
		ecmd->port = PORT_BNC;
		ecmd->speed = 2;
		break;
	default:
		ecmd->port = PORT_TP;
		ecmd->speed = SPEED_10;
		break;
	}

	if (dr32(MacMode) & FullDuplex)
		ecmd->duplex = DUPLEX_FULL;
	else
		ecmd->duplex = DUPLEX_HALF;

	if (de->media_lock)
		ecmd->autoneg = AUTONEG_DISABLE;
	else
		ecmd->autoneg = AUTONEG_ENABLE;

	/* ignore maxtxpkt, maxrxpkt for now */

	return 0;
}