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
struct TYPE_5__ {int signal; int service; unsigned int length_high; unsigned int length_low; int /*<<< orphan*/  ifs; } ;
struct TYPE_6__ {TYPE_2__ plcp; } ;
struct txentry_desc {TYPE_3__ u; int /*<<< orphan*/  flags; } ;
struct sk_buff {int len; } ;
struct rt2x00_rate {int plcp; int flags; int bitrate; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_tx_rate {int flags; } ;
struct TYPE_4__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;

/* Variables and functions */
 int DEV_RATE_OFDM ; 
 int /*<<< orphan*/  ENTRY_TXD_FIRST_FRAGMENT ; 
 unsigned int GET_DURATION (unsigned int,int) ; 
 unsigned int GET_DURATION_RES (unsigned int,int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  IFS_BACKOFF ; 
 int /*<<< orphan*/  IFS_SIFS ; 
 scalar_t__ rt2x00crypto_tx_overhead (struct rt2x00_dev*,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00queue_create_tx_descriptor_plcp(struct rt2x00_dev *rt2x00dev,
						  struct sk_buff *skb,
						  struct txentry_desc *txdesc,
						  const struct rt2x00_rate *hwrate)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *txrate = &tx_info->control.rates[0];
	unsigned int data_length;
	unsigned int duration;
	unsigned int residual;

	/*
	 * Determine with what IFS priority this frame should be send.
	 * Set ifs to IFS_SIFS when the this is not the first fragment,
	 * or this fragment came after RTS/CTS.
	 */
	if (test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags))
		txdesc->u.plcp.ifs = IFS_BACKOFF;
	else
		txdesc->u.plcp.ifs = IFS_SIFS;

	/* Data length + CRC + Crypto overhead (IV/EIV/ICV/MIC) */
	data_length = skb->len + 4;
	data_length += rt2x00crypto_tx_overhead(rt2x00dev, skb);

	/*
	 * PLCP setup
	 * Length calculation depends on OFDM/CCK rate.
	 */
	txdesc->u.plcp.signal = hwrate->plcp;
	txdesc->u.plcp.service = 0x04;

	if (hwrate->flags & DEV_RATE_OFDM) {
		txdesc->u.plcp.length_high = (data_length >> 6) & 0x3f;
		txdesc->u.plcp.length_low = data_length & 0x3f;
	} else {
		/*
		 * Convert length to microseconds.
		 */
		residual = GET_DURATION_RES(data_length, hwrate->bitrate);
		duration = GET_DURATION(data_length, hwrate->bitrate);

		if (residual != 0) {
			duration++;

			/*
			 * Check if we need to set the Length Extension
			 */
			if (hwrate->bitrate == 110 && residual <= 30)
				txdesc->u.plcp.service |= 0x80;
		}

		txdesc->u.plcp.length_high = (duration >> 8) & 0xff;
		txdesc->u.plcp.length_low = duration & 0xff;

		/*
		 * When preamble is enabled we should set the
		 * preamble bit for the signal.
		 */
		if (txrate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			txdesc->u.plcp.signal |= 0x08;
	}
}