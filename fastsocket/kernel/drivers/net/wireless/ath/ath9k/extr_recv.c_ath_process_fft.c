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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_6__ {void* length; int /*<<< orphan*/  type; } ;
struct fft_sample_ht20 {int* data; int max_exp; TYPE_3__ tlv; int /*<<< orphan*/  tsf; int /*<<< orphan*/  bitmap_weight; int /*<<< orphan*/  max_index; void* max_magnitude; int /*<<< orphan*/  noise; int /*<<< orphan*/  rssi; void* freq; } ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_rx_status {int rs_datalen; scalar_t__ rs_phyerr; int /*<<< orphan*/  rs_rssi_ctl0; } ;
struct ath_radar_info {int pulse_bw_info; } ;
struct ath_hw {int /*<<< orphan*/  noise; TYPE_2__* curchan; } ;
struct ath_ht20_mag_info {int max_exp; int /*<<< orphan*/  all_bins; } ;
typedef  int /*<<< orphan*/  fft_sample ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_4__ {int center_freq; } ;

/* Variables and functions */
 scalar_t__ ATH9K_PHYERR_FALSE_RADAR_EXT ; 
 scalar_t__ ATH9K_PHYERR_RADAR ; 
 scalar_t__ ATH9K_PHYERR_SPECTRAL ; 
 int /*<<< orphan*/  ATH_FFT_SAMPLE_HT20 ; 
 int SPECTRAL_HT20_NUM_BINS ; 
 int SPECTRAL_HT20_TOTAL_DATA_LEN ; 
 int SPECTRAL_SCAN_BITMASK ; 
 void* __cpu_to_be16 (int) ; 
 int /*<<< orphan*/  __cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_debug_send_fft_sample (struct ath_softc*,TYPE_3__*) ; 
 int /*<<< orphan*/  fix_rssi_inv_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  spectral_bitmap_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spectral_max_index (int /*<<< orphan*/ ) ; 
 int spectral_max_magnitude (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath_process_fft(struct ath_softc *sc, struct ieee80211_hdr *hdr,
			   struct ath_rx_status *rs, u64 tsf)
{
#ifdef CONFIG_ATH9K_DEBUGFS
	struct ath_hw *ah = sc->sc_ah;
	u8 bins[SPECTRAL_HT20_NUM_BINS];
	u8 *vdata = (u8 *)hdr;
	struct fft_sample_ht20 fft_sample;
	struct ath_radar_info *radar_info;
	struct ath_ht20_mag_info *mag_info;
	int len = rs->rs_datalen;
	int dc_pos;
	u16 length, max_magnitude;

	/* AR9280 and before report via ATH9K_PHYERR_RADAR, AR93xx and newer
	 * via ATH9K_PHYERR_SPECTRAL. Haven't seen ATH9K_PHYERR_FALSE_RADAR_EXT
	 * yet, but this is supposed to be possible as well.
	 */
	if (rs->rs_phyerr != ATH9K_PHYERR_RADAR &&
	    rs->rs_phyerr != ATH9K_PHYERR_FALSE_RADAR_EXT &&
	    rs->rs_phyerr != ATH9K_PHYERR_SPECTRAL)
		return 0;

	/* check if spectral scan bit is set. This does not have to be checked
	 * if received through a SPECTRAL phy error, but shouldn't hurt.
	 */
	radar_info = ((struct ath_radar_info *)&vdata[len]) - 1;
	if (!(radar_info->pulse_bw_info & SPECTRAL_SCAN_BITMASK))
		return 0;

	/* Variation in the data length is possible and will be fixed later.
	 * Note that we only support HT20 for now.
	 *
	 * TODO: add HT20_40 support as well.
	 */
	if ((len > SPECTRAL_HT20_TOTAL_DATA_LEN + 2) ||
	    (len < SPECTRAL_HT20_TOTAL_DATA_LEN - 1))
		return 1;

	fft_sample.tlv.type = ATH_FFT_SAMPLE_HT20;
	length = sizeof(fft_sample) - sizeof(fft_sample.tlv);
	fft_sample.tlv.length = __cpu_to_be16(length);

	fft_sample.freq = __cpu_to_be16(ah->curchan->chan->center_freq);
	fft_sample.rssi = fix_rssi_inv_only(rs->rs_rssi_ctl0);
	fft_sample.noise = ah->noise;

	switch (len - SPECTRAL_HT20_TOTAL_DATA_LEN) {
	case 0:
		/* length correct, nothing to do. */
		memcpy(bins, vdata, SPECTRAL_HT20_NUM_BINS);
		break;
	case -1:
		/* first byte missing, duplicate it. */
		memcpy(&bins[1], vdata, SPECTRAL_HT20_NUM_BINS - 1);
		bins[0] = vdata[0];
		break;
	case 2:
		/* MAC added 2 extra bytes at bin 30 and 32, remove them. */
		memcpy(bins, vdata, 30);
		bins[30] = vdata[31];
		memcpy(&bins[31], &vdata[33], SPECTRAL_HT20_NUM_BINS - 31);
		break;
	case 1:
		/* MAC added 2 extra bytes AND first byte is missing. */
		bins[0] = vdata[0];
		memcpy(&bins[0], vdata, 30);
		bins[31] = vdata[31];
		memcpy(&bins[32], &vdata[33], SPECTRAL_HT20_NUM_BINS - 32);
		break;
	default:
		return 1;
	}

	/* DC value (value in the middle) is the blind spot of the spectral
	 * sample and invalid, interpolate it.
	 */
	dc_pos = SPECTRAL_HT20_NUM_BINS / 2;
	bins[dc_pos] = (bins[dc_pos + 1] + bins[dc_pos - 1]) / 2;

	/* mag data is at the end of the frame, in front of radar_info */
	mag_info = ((struct ath_ht20_mag_info *)radar_info) - 1;

	/* copy raw bins without scaling them */
	memcpy(fft_sample.data, bins, SPECTRAL_HT20_NUM_BINS);
	fft_sample.max_exp = mag_info->max_exp & 0xf;

	max_magnitude = spectral_max_magnitude(mag_info->all_bins);
	fft_sample.max_magnitude = __cpu_to_be16(max_magnitude);
	fft_sample.max_index = spectral_max_index(mag_info->all_bins);
	fft_sample.bitmap_weight = spectral_bitmap_weight(mag_info->all_bins);
	fft_sample.tsf = __cpu_to_be64(tsf);

	ath_debug_send_fft_sample(sc, &fft_sample.tlv);
	return 1;
#else
	return 0;
#endif
}