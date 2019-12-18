#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int* phy; size_t phyNum; scalar_t__ duplex; TYPE_1__* adapter; void* tlanFullDuplex; int /*<<< orphan*/  neg_be_verbose; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ TLanPrivateInfo ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MII_AN_ADV ; 
 int /*<<< orphan*/  MII_AN_LPA ; 
 int MII_GC_AUTOENB ; 
 int MII_GC_DUPLEX ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  MII_GEN_STS ; 
 int MII_GS_AUTOCMPLT ; 
 int TLAN_ADAPTER_USE_INTERN_10 ; 
 scalar_t__ TLAN_DUPLEX_FULL ; 
 int TLAN_NET_CFG_1CHAN ; 
 int TLAN_NET_CFG_1FRAG ; 
 int TLAN_NET_CFG_PHY_EN ; 
 int /*<<< orphan*/  TLAN_NET_CONFIG ; 
 int /*<<< orphan*/  TLAN_TIMER_FINISH_RESET ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_FINISH_AN ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_PDOWN ; 
 int /*<<< orphan*/  TLan_DioWrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_MiiReadReg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TLan_MiiWriteReg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_SetTimer (struct net_device*,int,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void TLan_PhyFinishAutoNeg( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	u16		an_adv;
	u16		an_lpa;
	u16		data;
	u16		mode;
	u16		phy;
	u16		status;

	phy = priv->phy[priv->phyNum];

	TLan_MiiReadReg( dev, phy, MII_GEN_STS, &status );
	udelay( 1000 );
	TLan_MiiReadReg( dev, phy, MII_GEN_STS, &status );

	if ( ! ( status & MII_GS_AUTOCMPLT ) ) {
		/* Wait for 8 sec to give the process
		 * more time.  Perhaps we should fail after a while.
		 */
		 if (!priv->neg_be_verbose++) {
			 pr_info("TLAN:  Giving autonegotiation more time.\n");
		 	 pr_info("TLAN:  Please check that your adapter has\n");
		 	 pr_info("TLAN:  been properly connected to a HUB or Switch.\n");
			 pr_info("TLAN:  Trying to establish link in the background...\n");
		 }
		TLan_SetTimer( dev, (8*HZ), TLAN_TIMER_PHY_FINISH_AN );
		return;
	}

	printk( "TLAN: %s: Autonegotiation complete.\n", dev->name );
	TLan_MiiReadReg( dev, phy, MII_AN_ADV, &an_adv );
	TLan_MiiReadReg( dev, phy, MII_AN_LPA, &an_lpa );
	mode = an_adv & an_lpa & 0x03E0;
	if ( mode & 0x0100 ) {
		priv->tlanFullDuplex = TRUE;
	} else if ( ! ( mode & 0x0080 ) && ( mode & 0x0040 ) ) {
		priv->tlanFullDuplex = TRUE;
	}

	if ( ( ! ( mode & 0x0180 ) ) &&
	     ( priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10 ) &&
	     ( priv->phyNum != 0 ) ) {
		priv->phyNum = 0;
		data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN | TLAN_NET_CFG_PHY_EN;
		TLan_DioWrite16( dev->base_addr, TLAN_NET_CONFIG, data );
		TLan_SetTimer( dev, (400*HZ/1000), TLAN_TIMER_PHY_PDOWN );
		return;
	}

	if ( priv->phyNum == 0 ) {
		if ( ( priv->duplex == TLAN_DUPLEX_FULL ) ||
		     ( an_adv & an_lpa & 0x0040 ) ) {
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL,
					  MII_GC_AUTOENB | MII_GC_DUPLEX );
			pr_info("TLAN:  Starting internal PHY with FULL-DUPLEX\n" );
		} else {
			TLan_MiiWriteReg( dev, phy, MII_GEN_CTL, MII_GC_AUTOENB );
			pr_info( "TLAN:  Starting internal PHY with HALF-DUPLEX\n" );
		}
	}

	/* Wait for 100 ms.  No reason in partiticular.
	 */
	TLan_SetTimer( dev, (HZ/10), TLAN_TIMER_FINISH_RESET );

}