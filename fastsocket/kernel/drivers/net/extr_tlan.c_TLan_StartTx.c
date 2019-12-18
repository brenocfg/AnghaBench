#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct net_device {int name; int /*<<< orphan*/  trans_start; scalar_t__ base_addr; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  void* dma_addr_t ;
struct TYPE_8__ {scalar_t__ cStat; void* forward; TYPE_1__* buffer; scalar_t__ frameSize; } ;
struct TYPE_7__ {int txTail; int txInProgress; int /*<<< orphan*/  lock; TYPE_3__* txList; int /*<<< orphan*/  pciDev; int /*<<< orphan*/  txBusyCount; int /*<<< orphan*/  txHead; void* txListDMA; int /*<<< orphan*/  phyOnline; } ;
struct TYPE_6__ {int count; scalar_t__ address; } ;
typedef  TYPE_2__ TLanPrivateInfo ;
typedef  TYPE_3__ TLanList ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_INC (int,int) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ TLAN_CH_PARM ; 
 scalar_t__ TLAN_CSTAT_READY ; 
 scalar_t__ TLAN_CSTAT_UNUSED ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 void* TLAN_HC_GO ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int TLAN_LAST_BUFFER ; 
 scalar_t__ TLAN_MIN_FRAME_SIZE ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  TLan_StoreSKB (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned int max (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (void*,scalar_t__) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_padto (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t TLan_StartTx( struct sk_buff *skb, struct net_device *dev )
{
	TLanPrivateInfo *priv = netdev_priv(dev);
	dma_addr_t	tail_list_phys;
	TLanList	*tail_list;
	unsigned long	flags;
	unsigned int    txlen;

	if ( ! priv->phyOnline ) {
		TLAN_DBG( TLAN_DEBUG_TX, "TRANSMIT:  %s PHY is not ready\n",
			  dev->name );
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (skb_padto(skb, TLAN_MIN_FRAME_SIZE))
		return NETDEV_TX_OK;
	txlen = max(skb->len, (unsigned int)TLAN_MIN_FRAME_SIZE);

	tail_list = priv->txList + priv->txTail;
	tail_list_phys = priv->txListDMA + sizeof(TLanList) * priv->txTail;

	if ( tail_list->cStat != TLAN_CSTAT_UNUSED ) {
		TLAN_DBG( TLAN_DEBUG_TX,
			  "TRANSMIT:  %s is busy (Head=%d Tail=%d)\n",
			  dev->name, priv->txHead, priv->txTail );
		netif_stop_queue(dev);
		priv->txBusyCount++;
		return NETDEV_TX_BUSY;
	}

	tail_list->forward = 0;

	tail_list->buffer[0].address = pci_map_single(priv->pciDev,
						      skb->data, txlen,
						      PCI_DMA_TODEVICE);
	TLan_StoreSKB(tail_list, skb);

	tail_list->frameSize = (u16) txlen;
	tail_list->buffer[0].count = TLAN_LAST_BUFFER | (u32) txlen;
	tail_list->buffer[1].count = 0;
	tail_list->buffer[1].address = 0;

	spin_lock_irqsave(&priv->lock, flags);
	tail_list->cStat = TLAN_CSTAT_READY;
	if ( ! priv->txInProgress ) {
		priv->txInProgress = 1;
		TLAN_DBG( TLAN_DEBUG_TX,
			  "TRANSMIT:  Starting TX on buffer %d\n", priv->txTail );
		outl( tail_list_phys, dev->base_addr + TLAN_CH_PARM );
		outl( TLAN_HC_GO, dev->base_addr + TLAN_HOST_CMD );
	} else {
		TLAN_DBG( TLAN_DEBUG_TX, "TRANSMIT:  Adding buffer %d to TX channel\n",
			  priv->txTail );
		if ( priv->txTail == 0 ) {
			( priv->txList + ( TLAN_NUM_TX_LISTS - 1 ) )->forward
				= tail_list_phys;
		} else {
			( priv->txList + ( priv->txTail - 1 ) )->forward
				= tail_list_phys;
		}
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	CIRC_INC( priv->txTail, TLAN_NUM_TX_LISTS );

	dev->trans_start = jiffies;
	return NETDEV_TX_OK;

}