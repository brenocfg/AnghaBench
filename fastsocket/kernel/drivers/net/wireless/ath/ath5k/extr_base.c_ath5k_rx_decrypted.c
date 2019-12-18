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
struct sk_buff {int* data; unsigned int len; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath_common {int /*<<< orphan*/  keymap; } ;
struct ath5k_rx_status {int rs_status; scalar_t__ rs_keyix; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int AR5K_RXERR_DECRYPT ; 
 scalar_t__ AR5K_RXKEYIX_INVALID ; 
 unsigned int RX_FLAG_DECRYPTED ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ath5k_rx_decrypted(struct ath5k_hw *ah, struct sk_buff *skb,
		   struct ath5k_rx_status *rs)
{
	struct ath_common *common = ath5k_hw_common(ah);
	struct ieee80211_hdr *hdr = (void *)skb->data;
	unsigned int keyix, hlen;

	if (!(rs->rs_status & AR5K_RXERR_DECRYPT) &&
			rs->rs_keyix != AR5K_RXKEYIX_INVALID)
		return RX_FLAG_DECRYPTED;

	/* Apparently when a default key is used to decrypt the packet
	   the hw does not set the index used to decrypt.  In such cases
	   get the index from the packet. */
	hlen = ieee80211_hdrlen(hdr->frame_control);
	if (ieee80211_has_protected(hdr->frame_control) &&
	    !(rs->rs_status & AR5K_RXERR_DECRYPT) &&
	    skb->len >= hlen + 4) {
		keyix = skb->data[hlen + 3] >> 6;

		if (test_bit(keyix, common->keymap))
			return RX_FLAG_DECRYPTED;
	}

	return 0;
}