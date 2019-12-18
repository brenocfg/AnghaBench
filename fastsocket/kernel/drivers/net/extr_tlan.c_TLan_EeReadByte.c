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
typedef  int u8 ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ TLanPrivateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_EEPROM_ACK ; 
 int /*<<< orphan*/  TLAN_EEPROM_STOP ; 
 int /*<<< orphan*/  TLan_EeReceiveByte (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int TLan_EeSendByte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLan_EeSendStart (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int TLan_EeReadByte( struct net_device *dev, u8 ee_addr, u8 *data )
{
	int err;
	TLanPrivateInfo *priv = netdev_priv(dev);
	unsigned long flags = 0;
	int ret=0;

	spin_lock_irqsave(&priv->lock, flags);

	TLan_EeSendStart( dev->base_addr );
	err = TLan_EeSendByte( dev->base_addr, 0xA0, TLAN_EEPROM_ACK );
	if (err)
	{
		ret=1;
		goto fail;
	}
	err = TLan_EeSendByte( dev->base_addr, ee_addr, TLAN_EEPROM_ACK );
	if (err)
	{
		ret=2;
		goto fail;
	}
	TLan_EeSendStart( dev->base_addr );
	err = TLan_EeSendByte( dev->base_addr, 0xA1, TLAN_EEPROM_ACK );
	if (err)
	{
		ret=3;
		goto fail;
	}
	TLan_EeReceiveByte( dev->base_addr, data, TLAN_EEPROM_STOP );
fail:
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;

}