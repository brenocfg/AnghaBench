#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct TYPE_11__ {scalar_t__ chan; } ;
typedef  TYPE_3__ pc300dev_t ;
struct TYPE_12__ {int channel; scalar_t__ card; } ;
typedef  TYPE_4__ pc300ch_t ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ cpld_reg2; scalar_t__ falcbase; scalar_t__ scabase; } ;
struct TYPE_13__ {TYPE_2__ hw; } ;
typedef  TYPE_5__ pc300_t ;
struct TYPE_14__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_LOCK (TYPE_5__*,unsigned long) ; 
 int /*<<< orphan*/  CPC_UNLOCK (TYPE_5__*,unsigned long) ; 
 int CPLD_REG2_FALC_LED1 ; 
 scalar_t__ DMER ; 
 scalar_t__ ILAR ; 
 scalar_t__ PC300_TE ; 
 int cpc_readb (scalar_t__) ; 
 int /*<<< orphan*/  cpc_writeb (scalar_t__,int) ; 
 TYPE_6__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpc_tx_timeout(struct net_device *dev)
{
	pc300dev_t *d = (pc300dev_t *) dev_to_hdlc(dev)->priv;
	pc300ch_t *chan = (pc300ch_t *) d->chan;
	pc300_t *card = (pc300_t *) chan->card;
	int ch = chan->channel;
	unsigned long flags;
	u8 ilar;

	dev->stats.tx_errors++;
	dev->stats.tx_aborted_errors++;
	CPC_LOCK(card, flags);
	if ((ilar = cpc_readb(card->hw.scabase + ILAR)) != 0) {
		printk("%s: ILAR=0x%x\n", dev->name, ilar);
		cpc_writeb(card->hw.scabase + ILAR, ilar);
		cpc_writeb(card->hw.scabase + DMER, 0x80);
	}
	if (card->hw.type == PC300_TE) {
		cpc_writeb(card->hw.falcbase + card->hw.cpld_reg2,
			   cpc_readb(card->hw.falcbase + card->hw.cpld_reg2) &
			   ~(CPLD_REG2_FALC_LED1 << (2 * ch)));
	}
	dev->trans_start = jiffies;
	CPC_UNLOCK(card, flags);
	netif_wake_queue(dev);
}