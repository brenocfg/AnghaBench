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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct net_device {scalar_t__ base_addr; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {int cStat; } ;
struct TYPE_4__ {int tlanRev; int txHead; scalar_t__ txInProgress; scalar_t__ txListDMA; TYPE_2__* txList; int /*<<< orphan*/  txTail; } ;
typedef  TYPE_1__ TLanPrivateInfo ;
typedef  TYPE_2__ TLanList ;

/* Variables and functions */
 scalar_t__ TLAN_CH_PARM ; 
 int TLAN_CSTAT_READY ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 int TLAN_HC_GO ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 TLan_HandleTxEOC( struct net_device *dev, u16 host_int )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	TLanList		*head_list;
	dma_addr_t		head_list_phys;
	u32			ack = 1;

	host_int = 0;
	if ( priv->tlanRev < 0x30 ) {
		TLAN_DBG( TLAN_DEBUG_TX,
			  "TRANSMIT:  Handling TX EOC (Head=%d Tail=%d) -- IRQ\n",
			  priv->txHead, priv->txTail );
		head_list = priv->txList + priv->txHead;
		head_list_phys = priv->txListDMA + sizeof(TLanList) * priv->txHead;
		if ( ( head_list->cStat & TLAN_CSTAT_READY ) == TLAN_CSTAT_READY ) {
			netif_stop_queue(dev);
			outl( head_list_phys, dev->base_addr + TLAN_CH_PARM );
			ack |= TLAN_HC_GO;
		} else {
			priv->txInProgress = 0;
		}
	}

	return ack;

}