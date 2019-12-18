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
struct net_device {int base_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int TLAN_DIO_ADR ; 
 int TLAN_DIO_DATA ; 
 int TLAN_NET_SIO ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MCLK ; 
 int /*<<< orphan*/  TLAN_NET_SIO_MINTEN ; 
 int /*<<< orphan*/  TLan_ClearBit (int /*<<< orphan*/ ,int) ; 
 int TLan_GetBit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLan_MiiSendData (int,int,int) ; 
 int /*<<< orphan*/  TLan_MiiSync (int) ; 
 int /*<<< orphan*/  TLan_SetBit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_irq () ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void TLan_MiiWriteReg( struct net_device *dev, u16 phy, u16 reg, u16 val )
{
	u16	sio;
	int	minten;
	unsigned long flags = 0;
	TLanPrivateInfo *priv = netdev_priv(dev);

	outw(TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR);
	sio = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;

	if (!in_irq())
		spin_lock_irqsave(&priv->lock, flags);

	TLan_MiiSync( dev->base_addr );

	minten = TLan_GetBit( TLAN_NET_SIO_MINTEN, sio );
	if ( minten )
		TLan_ClearBit( TLAN_NET_SIO_MINTEN, sio );

	TLan_MiiSendData( dev->base_addr, 0x1, 2 );	/* Start ( 01b ) */
	TLan_MiiSendData( dev->base_addr, 0x1, 2 );	/* Write ( 01b ) */
	TLan_MiiSendData( dev->base_addr, phy, 5 );	/* Device #      */
	TLan_MiiSendData( dev->base_addr, reg, 5 );	/* Register #    */

	TLan_MiiSendData( dev->base_addr, 0x2, 2 );	/* Send ACK */
	TLan_MiiSendData( dev->base_addr, val, 16 );	/* Send Data */

	TLan_ClearBit( TLAN_NET_SIO_MCLK, sio );	/* Idle cycle */
	TLan_SetBit( TLAN_NET_SIO_MCLK, sio );

	if ( minten )
		TLan_SetBit( TLAN_NET_SIO_MINTEN, sio );

	if (!in_irq())
		spin_unlock_irqrestore(&priv->lock, flags);

}