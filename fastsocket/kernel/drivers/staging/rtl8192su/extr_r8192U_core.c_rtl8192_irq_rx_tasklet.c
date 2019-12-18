#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ cb; } ;
struct rtl8192_rx_info {int out_pipe; } ;
struct r8192_priv {TYPE_1__* ops; int /*<<< orphan*/  IrpPendingCount; int /*<<< orphan*/  skb_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rtl819x_rx_cmd ) (struct sk_buff*) ;int /*<<< orphan*/  (* rtl819x_rx_nomal ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_RECV ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*) ; 

void rtl8192_irq_rx_tasklet(struct r8192_priv *priv)
{
        struct sk_buff *skb;
	struct rtl8192_rx_info *info;

        while (NULL != (skb = skb_dequeue(&priv->skb_queue))) {
		info = (struct rtl8192_rx_info *)skb->cb;
                switch (info->out_pipe) {
		/* Nomal packet pipe */
			case 3:
				//RT_TRACE(COMP_RECV, "normal in-pipe index(%d)\n",info->out_pipe);
				priv->IrpPendingCount--;
				priv->ops->rtl819x_rx_nomal(skb);
				break;

				/* Command packet pipe */
			case 9:
				RT_TRACE(COMP_RECV, "command in-pipe index(%d)\n",\
						info->out_pipe);
				priv->ops->rtl819x_rx_cmd(skb);
				break;

			default: /* should never get here! */
				RT_TRACE(COMP_ERR, "Unknown in-pipe index(%d)\n",\
						info->out_pipe);
				dev_kfree_skb(skb);
				break;

		}
        }
}