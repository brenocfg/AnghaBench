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
typedef  int /*<<< orphan*/  u32 ;
struct usbnet {scalar_t__* data; } ;
struct smsc95xx_priv {scalar_t__ use_rx_csum; scalar_t__ use_tx_csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  COE_CR ; 
 int /*<<< orphan*/  Rx_COE_EN_ ; 
 int /*<<< orphan*/  Tx_COE_EN_ ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devwarn (struct usbnet*,char*,int) ; 
 scalar_t__ netif_msg_hw (struct usbnet*) ; 
 int smsc95xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smsc95xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc95xx_set_csums(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	u32 read_buf;
	int ret = smsc95xx_read_reg(dev, COE_CR, &read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to read COE_CR: %d", ret);
		return ret;
	}

	if (pdata->use_tx_csum)
		read_buf |= Tx_COE_EN_;
	else
		read_buf &= ~Tx_COE_EN_;

	if (pdata->use_rx_csum)
		read_buf |= Rx_COE_EN_;
	else
		read_buf &= ~Rx_COE_EN_;

	ret = smsc95xx_write_reg(dev, COE_CR, read_buf);
	if (ret < 0) {
		devwarn(dev, "Failed to write COE_CR: %d", ret);
		return ret;
	}

	if (netif_msg_hw(dev))
		devdbg(dev, "COE_CR = 0x%08x", read_buf);
	return 0;
}