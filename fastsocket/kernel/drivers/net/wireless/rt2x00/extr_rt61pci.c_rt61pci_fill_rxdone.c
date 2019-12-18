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
typedef  int /*<<< orphan*/  u32 ;
struct rxdone_entry_desc {scalar_t__ cipher; scalar_t__ cipher_status; int /*<<< orphan*/  dev_flags; void* size; int /*<<< orphan*/  rssi; void* signal; int /*<<< orphan*/  flags; int /*<<< orphan*/  icv; int /*<<< orphan*/ * iv; } ;
struct rt2x00_dev {int dummy; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {struct queue_entry_priv_mmio* priv_data; TYPE_1__* queue; } ;
struct TYPE_2__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 scalar_t__ CIPHER_NONE ; 
 int /*<<< orphan*/  RXDONE_CRYPTO_ICV ; 
 int /*<<< orphan*/  RXDONE_CRYPTO_IV ; 
 int /*<<< orphan*/  RXDONE_MY_BSS ; 
 int /*<<< orphan*/  RXDONE_SIGNAL_BITRATE ; 
 int /*<<< orphan*/  RXDONE_SIGNAL_PLCP ; 
 int /*<<< orphan*/  RXD_W0_CIPHER_ALG ; 
 int /*<<< orphan*/  RXD_W0_CIPHER_ERROR ; 
 int /*<<< orphan*/  RXD_W0_CRC_ERROR ; 
 int /*<<< orphan*/  RXD_W0_DATABYTE_COUNT ; 
 int /*<<< orphan*/  RXD_W0_MY_BSS ; 
 int /*<<< orphan*/  RXD_W0_OFDM ; 
 int /*<<< orphan*/  RXD_W1_SIGNAL ; 
 scalar_t__ RX_CRYPTO_FAIL_MIC ; 
 scalar_t__ RX_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_STRIPPED ; 
 int /*<<< orphan*/  _rt2x00_desc_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt61pci_agc_to_rssi (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt61pci_fill_rxdone(struct queue_entry *entry,
				struct rxdone_entry_desc *rxdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word0;
	u32 word1;

	rt2x00_desc_read(entry_priv->desc, 0, &word0);
	rt2x00_desc_read(entry_priv->desc, 1, &word1);

	if (rt2x00_get_field32(word0, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	rxdesc->cipher = rt2x00_get_field32(word0, RXD_W0_CIPHER_ALG);
	rxdesc->cipher_status = rt2x00_get_field32(word0, RXD_W0_CIPHER_ERROR);

	if (rxdesc->cipher != CIPHER_NONE) {
		_rt2x00_desc_read(entry_priv->desc, 2, &rxdesc->iv[0]);
		_rt2x00_desc_read(entry_priv->desc, 3, &rxdesc->iv[1]);
		rxdesc->dev_flags |= RXDONE_CRYPTO_IV;

		_rt2x00_desc_read(entry_priv->desc, 4, &rxdesc->icv);
		rxdesc->dev_flags |= RXDONE_CRYPTO_ICV;

		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. It has provided the data separately but rt2x00lib
		 * should decide if it should be reinserted.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has already checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		if (rxdesc->cipher_status == RX_CRYPTO_SUCCESS)
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		else if (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC)
			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
	}

	/*
	 * Obtain the status about this packet.
	 * When frame was received with an OFDM bitrate,
	 * the signal is the PLCP value. If it was received with
	 * a CCK bitrate the signal is the rate in 100kbit/s.
	 */
	rxdesc->signal = rt2x00_get_field32(word1, RXD_W1_SIGNAL);
	rxdesc->rssi = rt61pci_agc_to_rssi(rt2x00dev, word1);
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	if (rt2x00_get_field32(word0, RXD_W0_OFDM))
		rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	else
		rxdesc->dev_flags |= RXDONE_SIGNAL_BITRATE;
	if (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;
}