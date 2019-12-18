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
struct sk_buff {int dummy; } ;
struct ipw_tty {int dummy; } ;
struct ipw_network {int ras_control_lines; int /*<<< orphan*/  close_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ppp_channel; struct ipw_tty*** associated_ttys; } ;

/* Variables and functions */
 unsigned int IPW_CHANNEL_RAS ; 
 int IPW_CONTROL_LINE_DCD ; 
 int MAX_ASSOCIATED_TTYS ; 
 struct sk_buff* ipw_packet_received_skb (unsigned char*,unsigned int) ; 
 scalar_t__ ipwireless_tty_is_modem (struct ipw_tty*) ; 
 int /*<<< orphan*/  ipwireless_tty_received (struct ipw_tty*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_input (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipwireless_network_packet_received(struct ipw_network *network,
					unsigned int channel_idx,
					unsigned char *data,
					unsigned int length)
{
	int i;
	unsigned long flags;

	for (i = 0; i < MAX_ASSOCIATED_TTYS; i++) {
		struct ipw_tty *tty = network->associated_ttys[channel_idx][i];

		if (!tty)
			continue;

		/*
		 * If it's associated with a tty (other than the RAS channel
		 * when we're online), then send the data to that tty.  The RAS
		 * channel's data is handled above - it always goes through
		 * ppp_generic.
		 */
		if (channel_idx == IPW_CHANNEL_RAS
				&& (network->ras_control_lines &
					IPW_CONTROL_LINE_DCD) != 0
				&& ipwireless_tty_is_modem(tty)) {
			/*
			 * If data came in on the RAS channel and this tty is
			 * the modem tty, and we are online, then we send it to
			 * the PPP layer.
			 */
			mutex_lock(&network->close_lock);
			spin_lock_irqsave(&network->lock, flags);
			if (network->ppp_channel != NULL) {
				struct sk_buff *skb;

				spin_unlock_irqrestore(&network->lock,
						flags);

				/* Send the data to the ppp_generic module. */
				skb = ipw_packet_received_skb(data, length);
				ppp_input(network->ppp_channel, skb);
			} else
				spin_unlock_irqrestore(&network->lock,
						flags);
			mutex_unlock(&network->close_lock);
		}
		/* Otherwise we send it out the tty. */
		else
			ipwireless_tty_received(tty, data, length);
	}
}