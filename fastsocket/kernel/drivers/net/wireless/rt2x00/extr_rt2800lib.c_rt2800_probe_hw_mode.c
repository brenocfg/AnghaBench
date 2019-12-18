#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int rf; } ;
struct TYPE_9__ {int tx_params; int* rx_mask; } ;
struct TYPE_10__ {int ht_supported; int cap; int ampdu_factor; int ampdu_density; TYPE_3__ mcs; } ;
struct hw_mode_spec {int supported_rates; int num_channels; struct channel_info* channels_info; TYPE_4__ ht; void* channels; int /*<<< orphan*/  supported_bands; } ;
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; TYPE_1__ chip; TYPE_5__* hw; int /*<<< orphan*/  dev; struct hw_mode_spec spec; } ;
struct channel_info {char default_power1; char default_power2; } ;
struct TYPE_11__ {int flags; int max_rates; int max_report_rates; int max_rate_tries; TYPE_2__* wiphy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CAPABILITY_VCO_RECALIBRATION ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_RXPATH ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_TXPATH ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_A1 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_A2 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_BG1 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_BG2 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_HT_CAP_GRN_FLD ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int IEEE80211_HW_AMPDU_AGGREGATION ; 
 int IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING ; 
 int IEEE80211_HW_PS_NULLFUNC_STACK ; 
 int IEEE80211_HW_REPORTS_TX_ACK_STATUS ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SUPPORTS_HT_CCK_RATES ; 
 int IEEE80211_HW_SUPPORTS_PS ; 
 int /*<<< orphan*/  MAC_DEBUG_INDEX ; 
 int /*<<< orphan*/  MAC_DEBUG_INDEX_XTAL ; 
#define  RF2020 139 
 int RF2720 ; 
 int RF2750 ; 
 int RF2820 ; 
 int RF2850 ; 
#define  RF3020 138 
#define  RF3021 137 
#define  RF3022 136 
#define  RF3052 135 
#define  RF3290 134 
#define  RF3320 133 
 int RF3322 ; 
#define  RF5360 132 
#define  RF5370 131 
#define  RF5372 130 
#define  RF5390 129 
#define  RF5392 128 
 int RF5592 ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  SUPPORT_BAND_2GHZ ; 
 int /*<<< orphan*/  SUPPORT_BAND_5GHZ ; 
 int SUPPORT_RATE_CCK ; 
 int SUPPORT_RATE_OFDM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct channel_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* rf_vals ; 
 void* rf_vals_3x ; 
 void* rf_vals_5592_xtal20 ; 
 void* rf_vals_5592_xtal40 ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* rt2x00_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_is_pci (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_is_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int) ; 

__attribute__((used)) static int rt2800_probe_hw_mode(struct rt2x00_dev *rt2x00dev)
{
	struct hw_mode_spec *spec = &rt2x00dev->spec;
	struct channel_info *info;
	char *default_power1;
	char *default_power2;
	unsigned int i;
	u16 eeprom;
	u32 reg;

	/*
	 * Disable powersaving as default on PCI devices.
	 */
	if (rt2x00_is_pci(rt2x00dev) || rt2x00_is_soc(rt2x00dev))
		rt2x00dev->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	/*
	 * Initialize all hw fields.
	 */
	rt2x00dev->hw->flags =
	    IEEE80211_HW_SIGNAL_DBM |
	    IEEE80211_HW_SUPPORTS_PS |
	    IEEE80211_HW_PS_NULLFUNC_STACK |
	    IEEE80211_HW_AMPDU_AGGREGATION |
	    IEEE80211_HW_REPORTS_TX_ACK_STATUS |
	    IEEE80211_HW_SUPPORTS_HT_CCK_RATES;

	/*
	 * Don't set IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING for USB devices
	 * unless we are capable of sending the buffered frames out after the
	 * DTIM transmission using rt2x00lib_beacondone. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some time.
	 */
	if (!rt2x00_is_usb(rt2x00dev))
		rt2x00dev->hw->flags |=
			IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING;

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2x00_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * As rt2800 has a global fallback table we cannot specify
	 * more then one tx rate per frame but since the hw will
	 * try several rates (based on the fallback table) we should
	 * initialize max_report_rates to the maximum number of rates
	 * we are going to try. Otherwise mac80211 will truncate our
	 * reported tx rates and the rc algortihm will end up with
	 * incorrect data.
	 */
	rt2x00dev->hw->max_rates = 1;
	rt2x00dev->hw->max_report_rates = 7;
	rt2x00dev->hw->max_rate_tries = 1;

	rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC_CONF0, &eeprom);

	/*
	 * Initialize hw_mode information.
	 */
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	if (rt2x00_rf(rt2x00dev, RF2820) ||
	    rt2x00_rf(rt2x00dev, RF2720)) {
		spec->num_channels = 14;
		spec->channels = rf_vals;
	} else if (rt2x00_rf(rt2x00dev, RF2850) ||
		   rt2x00_rf(rt2x00dev, RF2750)) {
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals);
		spec->channels = rf_vals;
	} else if (rt2x00_rf(rt2x00dev, RF3020) ||
		   rt2x00_rf(rt2x00dev, RF2020) ||
		   rt2x00_rf(rt2x00dev, RF3021) ||
		   rt2x00_rf(rt2x00dev, RF3022) ||
		   rt2x00_rf(rt2x00dev, RF3290) ||
		   rt2x00_rf(rt2x00dev, RF3320) ||
		   rt2x00_rf(rt2x00dev, RF3322) ||
		   rt2x00_rf(rt2x00dev, RF5360) ||
		   rt2x00_rf(rt2x00dev, RF5370) ||
		   rt2x00_rf(rt2x00dev, RF5372) ||
		   rt2x00_rf(rt2x00dev, RF5390) ||
		   rt2x00_rf(rt2x00dev, RF5392)) {
		spec->num_channels = 14;
		spec->channels = rf_vals_3x;
	} else if (rt2x00_rf(rt2x00dev, RF3052)) {
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_3x);
		spec->channels = rf_vals_3x;
	} else if (rt2x00_rf(rt2x00dev, RF5592)) {
		spec->supported_bands |= SUPPORT_BAND_5GHZ;

		rt2800_register_read(rt2x00dev, MAC_DEBUG_INDEX, &reg);
		if (rt2x00_get_field32(reg, MAC_DEBUG_INDEX_XTAL)) {
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal40);
			spec->channels = rf_vals_5592_xtal40;
		} else {
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal20);
			spec->channels = rf_vals_5592_xtal20;
		}
	}

	if (WARN_ON_ONCE(!spec->channels))
		return -ENODEV;

	/*
	 * Initialize HT information.
	 */
	if (!rt2x00_rf(rt2x00dev, RF2020))
		spec->ht.ht_supported = true;
	else
		spec->ht.ht_supported = false;

	spec->ht.cap =
	    IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	    IEEE80211_HT_CAP_GRN_FLD |
	    IEEE80211_HT_CAP_SGI_20 |
	    IEEE80211_HT_CAP_SGI_40;

	if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) >= 2)
		spec->ht.cap |= IEEE80211_HT_CAP_TX_STBC;

	spec->ht.cap |=
	    rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) <<
		IEEE80211_HT_CAP_RX_STBC_SHIFT;

	spec->ht.ampdu_factor = 3;
	spec->ht.ampdu_density = 4;
	spec->ht.mcs.tx_params =
	    IEEE80211_HT_MCS_TX_DEFINED |
	    IEEE80211_HT_MCS_TX_RX_DIFF |
	    ((rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) - 1) <<
		IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);

	switch (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH)) {
	case 3:
		spec->ht.mcs.rx_mask[2] = 0xff;
	case 2:
		spec->ht.mcs.rx_mask[1] = 0xff;
	case 1:
		spec->ht.mcs.rx_mask[0] = 0xff;
		spec->ht.mcs.rx_mask[4] = 0x1; /* MCS32 */
		break;
	}

	/*
	 * Create channel information array
	 */
	info = kcalloc(spec->num_channels, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	spec->channels_info = info;

	default_power1 = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG1);
	default_power2 = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG2);

	for (i = 0; i < 14; i++) {
		info[i].default_power1 = default_power1[i];
		info[i].default_power2 = default_power2[i];
	}

	if (spec->num_channels > 14) {
		default_power1 = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_A1);
		default_power2 = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_A2);

		for (i = 14; i < spec->num_channels; i++) {
			info[i].default_power1 = default_power1[i - 14];
			info[i].default_power2 = default_power2[i - 14];
		}
	}

	switch (rt2x00dev->chip.rf) {
	case RF2020:
	case RF3020:
	case RF3021:
	case RF3022:
	case RF3320:
	case RF3052:
	case RF3290:
	case RF5360:
	case RF5370:
	case RF5372:
	case RF5390:
	case RF5392:
		__set_bit(CAPABILITY_VCO_RECALIBRATION, &rt2x00dev->cap_flags);
		break;
	}

	return 0;
}