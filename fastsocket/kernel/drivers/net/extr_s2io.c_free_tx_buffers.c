#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tx_fifo_config {int fifo_len; } ;
struct swStat {int /*<<< orphan*/  mem_freed; } ;
struct stat_block {struct swStat sw_stat; } ;
struct sk_buff {scalar_t__ truesize; } ;
struct mac_info {struct fifo_info* fifos; struct stat_block* stats_info; } ;
struct config_param {int tx_fifo_num; struct tx_fifo_config* tx_cfg; } ;
struct s2io_nic {struct mac_info mac_control; struct config_param config; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct fifo_info {int /*<<< orphan*/  tx_lock; TYPE_3__ tx_curr_put_info; TYPE_2__ tx_curr_get_info; TYPE_1__* list_info; } ;
struct TxD {int dummy; } ;
struct TYPE_4__ {scalar_t__ list_virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  INTR_DBG ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* s2io_txdl_getskb (struct fifo_info*,struct TxD*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_tx_buffers(struct s2io_nic *nic)
{
	struct net_device *dev = nic->dev;
	struct sk_buff *skb;
	struct TxD *txdp;
	int i, j;
	int cnt = 0;
	struct config_param *config = &nic->config;
	struct mac_info *mac_control = &nic->mac_control;
	struct stat_block *stats = mac_control->stats_info;
	struct swStat *swstats = &stats->sw_stat;

	for (i = 0; i < config->tx_fifo_num; i++) {
		struct tx_fifo_config *tx_cfg = &config->tx_cfg[i];
		struct fifo_info *fifo = &mac_control->fifos[i];
		unsigned long flags;

		spin_lock_irqsave(&fifo->tx_lock, flags);
		for (j = 0; j < tx_cfg->fifo_len; j++) {
			txdp = (struct TxD *)fifo->list_info[j].list_virt_addr;
			skb = s2io_txdl_getskb(&mac_control->fifos[i], txdp, j);
			if (skb) {
				swstats->mem_freed += skb->truesize;
				dev_kfree_skb(skb);
				cnt++;
			}
		}
		DBG_PRINT(INTR_DBG,
			  "%s: forcibly freeing %d skbs on FIFO%d\n",
			  dev->name, cnt, i);
		fifo->tx_curr_get_info.offset = 0;
		fifo->tx_curr_put_info.offset = 0;
		spin_unlock_irqrestore(&fifo->tx_lock, flags);
	}
}