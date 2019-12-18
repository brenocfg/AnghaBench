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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int base_addr; } ;
struct TYPE_5__ {int tlanRev; int aui; scalar_t__ duplex; scalar_t__ phyNum; TYPE_1__* adapter; int /*<<< orphan*/  tlanFullDuplex; scalar_t__ phyOnline; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ TLanPrivateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TLAN_ACOMMIT ; 
 int TLAN_ADAPTER_BIT_RATE_PHY ; 
 int TLAN_ADAPTER_UNMANAGED_PHY ; 
 int TLAN_AREG_0 ; 
 int TLAN_DIO_ADR ; 
 int TLAN_DIO_DATA ; 
 scalar_t__ TLAN_DUPLEX_FULL ; 
 int TLAN_HASH_2 ; 
 int TLAN_HC_AD_RST ; 
 int TLAN_HC_INT_OFF ; 
 int TLAN_HC_LD_THR ; 
 int TLAN_HC_LD_TMR ; 
 int TLAN_HOST_CMD ; 
 int TLAN_ID_RX_EOC ; 
 int TLAN_ID_TX_EOC ; 
 int /*<<< orphan*/  TLAN_INT_DIS ; 
 int TLAN_NET_CFG_1CHAN ; 
 int TLAN_NET_CFG_1FRAG ; 
 int TLAN_NET_CFG_BIT ; 
 int TLAN_NET_CFG_PHY_EN ; 
 int /*<<< orphan*/  TLAN_NET_CONFIG ; 
 int TLAN_NET_SIO ; 
 int /*<<< orphan*/  TLAN_NET_SIO_NMRST ; 
 int /*<<< orphan*/  TLan_DioWrite16 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_DioWrite32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_DioWrite8 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_FinishReset (struct net_device*) ; 
 int /*<<< orphan*/  TLan_PhyDetect (struct net_device*) ; 
 int /*<<< orphan*/  TLan_PhyPowerDown (struct net_device*) ; 
 int /*<<< orphan*/  TLan_SetBit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int inl (int) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
TLan_ResetAdapter( struct net_device *dev )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	int		i;
	u32		addr;
	u32		data;
	u8		data8;

	priv->tlanFullDuplex = FALSE;
	priv->phyOnline=0;
	netif_carrier_off(dev);

/*  1.	Assert reset bit. */

	data = inl(dev->base_addr + TLAN_HOST_CMD);
	data |= TLAN_HC_AD_RST;
	outl(data, dev->base_addr + TLAN_HOST_CMD);

	udelay(1000);

/*  2.	Turn off interrupts. ( Probably isn't necessary ) */

	data = inl(dev->base_addr + TLAN_HOST_CMD);
	data |= TLAN_HC_INT_OFF;
	outl(data, dev->base_addr + TLAN_HOST_CMD);

/*  3.	Clear AREGs and HASHs. */

 	for ( i = TLAN_AREG_0; i <= TLAN_HASH_2; i += 4 ) {
		TLan_DioWrite32( dev->base_addr, (u16) i, 0 );
	}

/*  4.	Setup NetConfig register. */

	data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN | TLAN_NET_CFG_PHY_EN;
	TLan_DioWrite16( dev->base_addr, TLAN_NET_CONFIG, (u16) data );

/*  5.	Load Ld_Tmr and Ld_Thr in HOST_CMD. */

 	outl( TLAN_HC_LD_TMR | 0x3f, dev->base_addr + TLAN_HOST_CMD );
 	outl( TLAN_HC_LD_THR | 0x9, dev->base_addr + TLAN_HOST_CMD );

/*  6.	Unreset the MII by setting NMRST (in NetSio) to 1. */

	outw( TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR );
	addr = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;
	TLan_SetBit( TLAN_NET_SIO_NMRST, addr );

/*  7.	Setup the remaining registers. */

	if ( priv->tlanRev >= 0x30 ) {
		data8 = TLAN_ID_TX_EOC | TLAN_ID_RX_EOC;
		TLan_DioWrite8( dev->base_addr, TLAN_INT_DIS, data8 );
	}
	TLan_PhyDetect( dev );
	data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN;

	if ( priv->adapter->flags & TLAN_ADAPTER_BIT_RATE_PHY ) {
		data |= TLAN_NET_CFG_BIT;
		if ( priv->aui == 1 ) {
			TLan_DioWrite8( dev->base_addr, TLAN_ACOMMIT, 0x0a );
		} else if ( priv->duplex == TLAN_DUPLEX_FULL ) {
			TLan_DioWrite8( dev->base_addr, TLAN_ACOMMIT, 0x00 );
			priv->tlanFullDuplex = TRUE;
		} else {
			TLan_DioWrite8( dev->base_addr, TLAN_ACOMMIT, 0x08 );
		}
	}

	if ( priv->phyNum == 0 ) {
		data |= TLAN_NET_CFG_PHY_EN;
	}
	TLan_DioWrite16( dev->base_addr, TLAN_NET_CONFIG, (u16) data );

	if ( priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY ) {
		TLan_FinishReset( dev );
	} else {
		TLan_PhyPowerDown( dev );
	}

}