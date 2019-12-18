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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {scalar_t__ base_addr; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int tlanRev; int rxHead; int /*<<< orphan*/  rxEocCount; scalar_t__ rxListDMA; int /*<<< orphan*/  rxTail; } ;
typedef  TYPE_1__ TLanPrivateInfo ;
typedef  int /*<<< orphan*/  TLanList ;

/* Variables and functions */
 scalar_t__ TLAN_CH_PARM ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_RX ; 
 int TLAN_HC_GO ; 
 int TLAN_HC_RT ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 TLan_HandleRxEOC( struct net_device *dev, u16 host_int )
{
	TLanPrivateInfo	*priv = netdev_priv(dev);
	dma_addr_t	head_list_phys;
	u32		ack = 1;

	if (  priv->tlanRev < 0x30 ) {
		TLAN_DBG( TLAN_DEBUG_RX,
			  "RECEIVE:  Handling RX EOC (Head=%d Tail=%d) -- IRQ\n",
			  priv->rxHead, priv->rxTail );
		head_list_phys = priv->rxListDMA + sizeof(TLanList) * priv->rxHead;
		outl( head_list_phys, dev->base_addr + TLAN_CH_PARM );
		ack |= TLAN_HC_GO | TLAN_HC_RT;
		priv->rxEocCount++;
	}

	return ack;

}