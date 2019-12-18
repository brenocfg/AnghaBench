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
typedef  int u8 ;
struct netif {scalar_t__ state; } ;
struct bba_priv {int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBA_IMR ; 
 int BBA_IMR_RBFIM ; 
 int /*<<< orphan*/  BBA_IR ; 
 int BBA_IR_BUSEI ; 
 int BBA_IR_FIFOEI ; 
 int BBA_IR_FRAGI ; 
 int BBA_IR_RBFI ; 
 int BBA_IR_REI ; 
 int BBA_IR_RI ; 
 int BBA_IR_TEI ; 
 int BBA_IR_TI ; 
 int /*<<< orphan*/  BBA_LRPS ; 
 int /*<<< orphan*/  BBA_LTPS ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  __bba_rx_err (int,struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_tx_err (int,struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_tx_wake (struct bba_priv*) ; 
 int bba_in8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_out8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bba_start_rx (struct netif*,int) ; 

__attribute__((used)) static inline void bba_interrupt(struct netif *dev)
{
	u8 ir,imr,status,lrps,ltps;
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	ir = bba_in8(BBA_IR);
	imr = bba_in8(BBA_IMR);
	status = ir&imr;
	while(status) {
		LWIP_DEBUGF(NETIF_DEBUG,("bba_interrupt(%02x)\n",status));
		bba_out8(BBA_IR,status);
		if(status&BBA_IR_RBFI) {
			bba_out8(BBA_IMR,(bba_in8(BBA_IMR)&~BBA_IMR_RBFIM));
			priv->flag |= BBA_IMR_RBFIM;
		}
		if(status&(BBA_IR_RI|BBA_IR_RBFI)) {
			bba_start_rx(dev,0x20);
		}
		if(status&(BBA_IR_TI|BBA_IR_FIFOEI)) {
			__bba_tx_wake(priv);
		}
		if(status&(BBA_IR_RBFI|BBA_IR_REI)) {
			lrps = bba_in8(BBA_LRPS);
			__bba_rx_err(lrps,priv);
		}
		if(status&BBA_IR_TEI) {
			ltps = bba_in8(BBA_LTPS);
			__bba_tx_err(ltps,priv);
			__bba_tx_wake(priv);
		}
		if(status&BBA_IR_FRAGI) {
			LWIP_DEBUGF(NETIF_DEBUG,("bba_interrupt(BBA_IR_FRAGI)\n"));
		}
		if(status&BBA_IR_FIFOEI) {
			LWIP_DEBUGF(NETIF_DEBUG,("bba_interrupt(BBA_IR_FIFOEI)\n"));
		}
		if(status&BBA_IR_BUSEI) {
			LWIP_DEBUGF(NETIF_DEBUG,("bba_interrupt(BBA_IR_BUSEI)\n"));
		}

		ir = bba_in8(BBA_IR);
		imr = bba_in8(BBA_IMR);
		status = ir&imr;
	}
	LWIP_DEBUGF(NETIF_DEBUG,("bba_interrupt(exit)\n"));
}