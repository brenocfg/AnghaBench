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
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct lbs_private {int surpriseremoved; scalar_t__ resp_idx; struct if_cs_card* card; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/ * resp_len; int /*<<< orphan*/ * resp_buf; } ;
struct if_cs_card {struct lbs_private* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int IF_CS_BIT_EVENT ; 
 int IF_CS_BIT_MASK ; 
 int IF_CS_BIT_RESP ; 
 int IF_CS_BIT_RX ; 
 int IF_CS_BIT_TX ; 
 int /*<<< orphan*/  IF_CS_CARD_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int IF_CS_CARD_STATUS_MASK ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LBS_DEB_CS ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_receive_cmdres (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* if_cs_receive_data (struct lbs_private*) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_deb_cs (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_host_to_card_done (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_notify_command_response (struct lbs_private*,size_t) ; 
 int /*<<< orphan*/  lbs_process_rxed_packet (struct lbs_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  lbs_queue_event (struct lbs_private*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t if_cs_interrupt(int irq, void *data)
{
	struct if_cs_card *card = data;
	struct lbs_private *priv = card->priv;
	u16 cause;

	lbs_deb_enter(LBS_DEB_CS);

	/* Ask card interrupt cause register if there is something for us */
	cause = if_cs_read16(card, IF_CS_CARD_INT_CAUSE);
	lbs_deb_cs("cause 0x%04x\n", cause);

	if (cause == 0) {
		/* Not for us */
		return IRQ_NONE;
	}

	if (cause == 0xffff) {
		/* Read in junk, the card has probably been removed */
		card->priv->surpriseremoved = 1;
		return IRQ_HANDLED;
	}

	if (cause & IF_CS_BIT_RX) {
		struct sk_buff *skb;
		lbs_deb_cs("rx packet\n");
		skb = if_cs_receive_data(priv);
		if (skb)
			lbs_process_rxed_packet(priv, skb);
	}

	if (cause & IF_CS_BIT_TX) {
		lbs_deb_cs("tx done\n");
		lbs_host_to_card_done(priv);
	}

	if (cause & IF_CS_BIT_RESP) {
		unsigned long flags;
		u8 i;

		lbs_deb_cs("cmd resp\n");
		spin_lock_irqsave(&priv->driver_lock, flags);
		i = (priv->resp_idx == 0) ? 1 : 0;
		spin_unlock_irqrestore(&priv->driver_lock, flags);

		BUG_ON(priv->resp_len[i]);
		if_cs_receive_cmdres(priv, priv->resp_buf[i],
			&priv->resp_len[i]);

		spin_lock_irqsave(&priv->driver_lock, flags);
		lbs_notify_command_response(priv, i);
		spin_unlock_irqrestore(&priv->driver_lock, flags);
	}

	if (cause & IF_CS_BIT_EVENT) {
		u16 status = if_cs_read16(priv->card, IF_CS_CARD_STATUS);
		if_cs_write16(priv->card, IF_CS_HOST_INT_CAUSE,
			IF_CS_BIT_EVENT);
		lbs_queue_event(priv, (status & IF_CS_CARD_STATUS_MASK) >> 8);
	}

	/* Clear interrupt cause */
	if_cs_write16(card, IF_CS_CARD_INT_CAUSE, cause & IF_CS_BIT_MASK);

	lbs_deb_leave(LBS_DEB_CS);
	return IRQ_HANDLED;
}