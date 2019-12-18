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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct wl1251_rx_descriptor {int snr; int flags; int rate; int mod_pre; int /*<<< orphan*/  channel; scalar_t__ rssi; int /*<<< orphan*/  timestamp; } ;
struct wl1251 {scalar_t__ bss_type; scalar_t__ noise; } ;
struct ieee80211_rx_status {int flag; int rate_idx; int /*<<< orphan*/  band; int /*<<< orphan*/  freq; scalar_t__ signal; int /*<<< orphan*/  mactime; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int OFDM_RATE_BIT ; 
#define  RATE_11MBPS 137 
#define  RATE_18MBPS 136 
 int RATE_1MBPS ; 
#define  RATE_24MBPS 135 
#define  RATE_2MBPS 134 
#define  RATE_36MBPS 133 
#define  RATE_48MBPS 132 
#define  RATE_54MBPS 131 
#define  RATE_5_5MBPS 130 
#define  RATE_6MBPS 129 
#define  RATE_9MBPS 128 
 int RX_DESC_DECRYPT_FAIL ; 
 int RX_DESC_ENCRYPTION_MASK ; 
 int RX_DESC_MIC_FAIL ; 
 int RX_DESC_VALID_FCS ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_FAILED_FCS_CRC ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MACTIME_START ; 
 int RX_FLAG_MMIC_ERROR ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 int RX_FLAG_SHORTPRE ; 
 int SHORT_PREAMBLE_BIT ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int wl1251_acx_tsf_info (struct wl1251*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wl1251_rx_status(struct wl1251 *wl,
			     struct wl1251_rx_descriptor *desc,
			     struct ieee80211_rx_status *status,
			     u8 beacon)
{
	u64 mactime;
	int ret;

	memset(status, 0, sizeof(struct ieee80211_rx_status));

	status->band = IEEE80211_BAND_2GHZ;
	status->mactime = desc->timestamp;

	/*
	 * The rx status timestamp is a 32 bits value while the TSF is a
	 * 64 bits one.
	 * For IBSS merging, TSF is mandatory, so we have to get it
	 * somehow, so we ask for ACX_TSF_INFO.
	 * That could be moved to the get_tsf() hook, but unfortunately,
	 * this one must be atomic, while our SPI routines can sleep.
	 */
	if ((wl->bss_type == BSS_TYPE_IBSS) && beacon) {
		ret = wl1251_acx_tsf_info(wl, &mactime);
		if (ret == 0)
			status->mactime = mactime;
	}

	status->signal = desc->rssi;

	/*
	 * FIXME: guessing that snr needs to be divided by two, otherwise
	 * the values don't make any sense
	 */
	wl->noise = desc->rssi - desc->snr / 2;

	status->freq = ieee80211_channel_to_frequency(desc->channel,
						      status->band);

	status->flag |= RX_FLAG_MACTIME_START;

	if (desc->flags & RX_DESC_ENCRYPTION_MASK) {
		status->flag |= RX_FLAG_IV_STRIPPED | RX_FLAG_MMIC_STRIPPED;

		if (likely(!(desc->flags & RX_DESC_DECRYPT_FAIL)))
			status->flag |= RX_FLAG_DECRYPTED;

		if (unlikely(desc->flags & RX_DESC_MIC_FAIL))
			status->flag |= RX_FLAG_MMIC_ERROR;
	}

	if (unlikely(!(desc->flags & RX_DESC_VALID_FCS)))
		status->flag |= RX_FLAG_FAILED_FCS_CRC;

	switch (desc->rate) {
		/* skip 1 and 12 Mbps because they have same value 0x0a */
	case RATE_2MBPS:
		status->rate_idx = 1;
		break;
	case RATE_5_5MBPS:
		status->rate_idx = 2;
		break;
	case RATE_11MBPS:
		status->rate_idx = 3;
		break;
	case RATE_6MBPS:
		status->rate_idx = 4;
		break;
	case RATE_9MBPS:
		status->rate_idx = 5;
		break;
	case RATE_18MBPS:
		status->rate_idx = 7;
		break;
	case RATE_24MBPS:
		status->rate_idx = 8;
		break;
	case RATE_36MBPS:
		status->rate_idx = 9;
		break;
	case RATE_48MBPS:
		status->rate_idx = 10;
		break;
	case RATE_54MBPS:
		status->rate_idx = 11;
		break;
	}

	/* for 1 and 12 Mbps we have to check the modulation */
	if (desc->rate == RATE_1MBPS) {
		if (!(desc->mod_pre & OFDM_RATE_BIT))
			/* CCK -> RATE_1MBPS */
			status->rate_idx = 0;
		else
			/* OFDM -> RATE_12MBPS */
			status->rate_idx = 6;
	}

	if (desc->mod_pre & SHORT_PREAMBLE_BIT)
		status->flag |= RX_FLAG_SHORTPRE;
}