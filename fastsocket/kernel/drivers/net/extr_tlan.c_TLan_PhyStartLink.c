#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int* phy; size_t phyNum; scalar_t__ speed; scalar_t__ duplex; void* tlanFullDuplex; scalar_t__ aui; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MII_AN_ADV ; 
 int MII_GC_DUPLEX ; 
 int MII_GC_SPEEDSEL ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  MII_GEN_STS ; 
 int MII_GS_AUTONEG ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 scalar_t__ TLAN_DUPLEX_FULL ; 
 scalar_t__ TLAN_DUPLEX_HALF ; 
 int TLAN_NET_CFG_1CHAN ; 
 int TLAN_NET_CFG_1FRAG ; 
 int TLAN_NET_CFG_PHY_EN ; 
 int /*<<< orphan*/  TLAN_NET_CONFIG ; 
 scalar_t__ TLAN_SPEED_10 ; 
 scalar_t__ TLAN_SPEED_100 ; 
 int TLAN_TC_AUISEL ; 
 int /*<<< orphan*/  TLAN_TIMER_FINISH_RESET ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_FINISH_AN ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_PDOWN ; 
 int /*<<< orphan*/  TLAN_TLPHY_CTL ; 
 int /*<<< orphan*/  TLan_DioWrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_MiiReadReg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TLan_MiiWriteReg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_SetTimer (struct net_device*,int,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TLan_PhyStartLink( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	u16		ability;
	u16		control;
	u16		data;
	u16		phy;
	u16		status;
	u16		tctl;

	phy = priv->phy[priv->phyNum];
	TLAN_DBG( TLAN_DEBUG_GNRL, "%s: Trying to activate link.\n", dev->name );
	TLan_MiiReadReg( dev, phy, MII_GEN_STS, &status );
	TLan_MiiReadReg( dev, phy, MII_GEN_STS, &ability );

	if ( ( status & MII_GS_AUTONEG ) &&
	     ( ! priv->aui ) ) {
		ability = status >> 11;
		if ( priv->speed  == TLAN_SPEED_10 &&
		     priv->duplex == TLAN_DUPLEX_HALF) {
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x0000);
		} else if ( priv->speed == TLAN_SPEED_10 &&
			    priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlanFullDuplex = TRUE;
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x0100);
		} else if ( priv->speed == TLAN_SPEED_100 &&
			    priv->duplex == TLAN_DUPLEX_HALF) {
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x2000);
		} else if ( priv->speed == TLAN_SPEED_100 &&
			    priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlanFullDuplex = TRUE;
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x2100);
		} else {

			/* Set Auto-Neg advertisement */
			TLan_MiiWriteReg( dev, phy, MII_AN_ADV, (ability << 5) | 1);
			/* Enablee Auto-Neg */
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x1000 );
			/* Restart Auto-Neg */
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, 0x1200 );
			/* Wait for 4 sec for autonegotiation
		 	* to complete.  The max spec time is less than this
		 	* but the card need additional time to start AN.
		 	* .5 sec should be plenty extra.
		 	*/
			printk( "TLAN: %s: Starting autonegotiation.\n", dev->name );
			TLan_SetTimer( dev, (2*HZ), TLAN_TIMER_PHY_FINISH_AN );
			return;
		}

	}

	if ( ( priv->aui ) && ( priv->phyNum != 0 ) ) {
		priv->phyNum = 0;
		data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN | TLAN_NET_CFG_PHY_EN;
		TLan_DioWrite16( dev->base_addr, TLAN_NET_CONFIG, data );
		TLan_SetTimer( dev, (40*HZ/1000), TLAN_TIMER_PHY_PDOWN );
		return;
	}  else if ( priv->phyNum == 0 ) {
		control = 0;
        	TLan_MiiReadReg( dev, phy, TLAN_TLPHY_CTL, &tctl );
		if ( priv->aui ) {
                	tctl |= TLAN_TC_AUISEL;
		} else {
                	tctl &= ~TLAN_TC_AUISEL;
			if ( priv->duplex == TLAN_DUPLEX_FULL ) {
				control |= MII_GC_DUPLEX;
				priv->tlanFullDuplex = TRUE;
			}
			if ( priv->speed == TLAN_SPEED_100 ) {
				control |= MII_GC_SPEEDSEL;
			}
		}
		TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, control );
        	TLan_MiiWriteReg( dev, phy, TLAN_TLPHY_CTL, tctl );
	}

	/* Wait for 2 sec to give the transceiver time
	 * to establish link.
	 */
	TLan_SetTimer( dev, (4*HZ), TLAN_TIMER_FINISH_RESET );

}