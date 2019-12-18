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
typedef  int u16 ;
struct wmi_event_swba {int dummy; } ;
struct wmi_cmd_hdr {int /*<<< orphan*/  command_id; } ;
struct wmi {struct ath9k_htc_priv* drv_priv; int /*<<< orphan*/  wmi_lock; int /*<<< orphan*/  wmi_event_queue; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {TYPE_1__ tx; int /*<<< orphan*/  fatal_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ATH9K_HTC_OP_TX_DRAIN ; 
#define  WMI_FATAL_EVENTID 130 
#define  WMI_SWBA_EVENTID 129 
#define  WMI_TXSTATUS_EVENTID 128 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_htc_swba (struct ath9k_htc_priv*,struct wmi_event_swba*) ; 
 int /*<<< orphan*/  ath9k_htc_txstatus (struct ath9k_htc_priv*,void*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ath9k_wmi_event_tasklet(unsigned long data)
{
	struct wmi *wmi = (struct wmi *)data;
	struct ath9k_htc_priv *priv = wmi->drv_priv;
	struct wmi_cmd_hdr *hdr;
	void *wmi_event;
	struct wmi_event_swba *swba;
	struct sk_buff *skb = NULL;
	unsigned long flags;
	u16 cmd_id;

	do {
		spin_lock_irqsave(&wmi->wmi_lock, flags);
		skb = __skb_dequeue(&wmi->wmi_event_queue);
		if (!skb) {
			spin_unlock_irqrestore(&wmi->wmi_lock, flags);
			return;
		}
		spin_unlock_irqrestore(&wmi->wmi_lock, flags);

		hdr = (struct wmi_cmd_hdr *) skb->data;
		cmd_id = be16_to_cpu(hdr->command_id);
		wmi_event = skb_pull(skb, sizeof(struct wmi_cmd_hdr));

		switch (cmd_id) {
		case WMI_SWBA_EVENTID:
			swba = (struct wmi_event_swba *) wmi_event;
			ath9k_htc_swba(priv, swba);
			break;
		case WMI_FATAL_EVENTID:
			ieee80211_queue_work(wmi->drv_priv->hw,
					     &wmi->drv_priv->fatal_work);
			break;
		case WMI_TXSTATUS_EVENTID:
			spin_lock_bh(&priv->tx.tx_lock);
			if (priv->tx.flags & ATH9K_HTC_OP_TX_DRAIN) {
				spin_unlock_bh(&priv->tx.tx_lock);
				break;
			}
			spin_unlock_bh(&priv->tx.tx_lock);

			ath9k_htc_txstatus(priv, wmi_event);
			break;
		default:
			break;
		}

		kfree_skb(skb);
	} while (1);
}