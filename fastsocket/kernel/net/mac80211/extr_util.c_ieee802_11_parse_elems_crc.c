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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee802_11_elems {size_t const* ie_start; size_t total_len; int parse_error; size_t const* ssid; size_t ssid_len; size_t const* supp_rates; size_t supp_rates_len; size_t const* ds_params; size_t tim_len; size_t const* challenge; size_t challenge_len; size_t const* wmm_info; size_t wmm_info_len; size_t const* wmm_param; size_t wmm_param_len; size_t const* rsn; size_t rsn_len; size_t const* erp_info; size_t const* ext_supp_rates; size_t ext_supp_rates_len; size_t const* opmode_notif; size_t const* mesh_id; size_t mesh_id_len; size_t const* peering; size_t peering_len; size_t const* preq; size_t preq_len; size_t const* prep; size_t prep_len; size_t const* perr; size_t perr_len; size_t const* country_elem; size_t country_elem_len; size_t const* pwr_constr_elem; void* timeout_int; void* wide_bw_chansw_ie; void* sec_chan_offs; void* ext_chansw_ie; void* ch_switch_ie; void* rann; void* awake_window; void* mesh_config; void* vht_operation; void* vht_cap_elem; void* ht_operation; void* ht_cap_elem; void* tim; } ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct ieee80211_timeout_interval_ie {int dummy; } ;
struct ieee80211_tim_ie {int dummy; } ;
struct ieee80211_sec_chan_offs_ie {int dummy; } ;
struct ieee80211_rann_ie {int dummy; } ;
struct ieee80211_meshconf_ie {int dummy; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct ieee80211_ext_chansw_ie {int dummy; } ;
struct ieee80211_channel_sw_ie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int) ; 
#define  WLAN_EID_CF_PARAMS 160 
#define  WLAN_EID_CHALLENGE 159 
#define  WLAN_EID_CHANNEL_SWITCH 158 
#define  WLAN_EID_CHANNEL_SWITCH_WRAPPER 157 
#define  WLAN_EID_COUNTRY 156 
#define  WLAN_EID_DS_PARAMS 155 
#define  WLAN_EID_ERP_INFO 154 
#define  WLAN_EID_EXT_CHANSWITCH_ANN 153 
#define  WLAN_EID_EXT_SUPP_RATES 152 
#define  WLAN_EID_FH_PARAMS 151 
#define  WLAN_EID_HT_CAPABILITY 150 
#define  WLAN_EID_HT_OPERATION 149 
#define  WLAN_EID_IBSS_PARAMS 148 
#define  WLAN_EID_MESH_AWAKE_WINDOW 147 
#define  WLAN_EID_MESH_CONFIG 146 
#define  WLAN_EID_MESH_ID 145 
#define  WLAN_EID_OPMODE_NOTIF 144 
#define  WLAN_EID_PEER_MGMT 143 
#define  WLAN_EID_PERR 142 
#define  WLAN_EID_PREP 141 
#define  WLAN_EID_PREQ 140 
#define  WLAN_EID_PWR_CONSTRAINT 139 
#define  WLAN_EID_RANN 138 
#define  WLAN_EID_RSN 137 
#define  WLAN_EID_SECONDARY_CHANNEL_OFFSET 136 
#define  WLAN_EID_SSID 135 
#define  WLAN_EID_SUPP_RATES 134 
#define  WLAN_EID_TIM 133 
#define  WLAN_EID_TIMEOUT_INTERVAL 132 
#define  WLAN_EID_VENDOR_SPECIFIC 131 
#define  WLAN_EID_VHT_CAPABILITY 130 
#define  WLAN_EID_VHT_OPERATION 129 
#define  WLAN_EID_WIDE_BW_CHANNEL_SWITCH 128 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 size_t* cfg80211_find_ie (int const,size_t const*,size_t) ; 
 int /*<<< orphan*/  crc32_be (int /*<<< orphan*/ ,size_t const*,size_t) ; 
 int /*<<< orphan*/  memset (struct ieee802_11_elems*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seen_elems ; 
 int /*<<< orphan*/  test_bit (size_t,int /*<<< orphan*/ ) ; 

u32 ieee802_11_parse_elems_crc(const u8 *start, size_t len, bool action,
			       struct ieee802_11_elems *elems,
			       u64 filter, u32 crc)
{
	size_t left = len;
	const u8 *pos = start;
	bool calc_crc = filter != 0;
	DECLARE_BITMAP(seen_elems, 256);
	const u8 *ie;

	bitmap_zero(seen_elems, 256);
	memset(elems, 0, sizeof(*elems));
	elems->ie_start = start;
	elems->total_len = len;

	while (left >= 2) {
		u8 id, elen;
		bool elem_parse_failed;

		id = *pos++;
		elen = *pos++;
		left -= 2;

		if (elen > left) {
			elems->parse_error = true;
			break;
		}

		switch (id) {
		case WLAN_EID_SSID:
		case WLAN_EID_SUPP_RATES:
		case WLAN_EID_FH_PARAMS:
		case WLAN_EID_DS_PARAMS:
		case WLAN_EID_CF_PARAMS:
		case WLAN_EID_TIM:
		case WLAN_EID_IBSS_PARAMS:
		case WLAN_EID_CHALLENGE:
		case WLAN_EID_RSN:
		case WLAN_EID_ERP_INFO:
		case WLAN_EID_EXT_SUPP_RATES:
		case WLAN_EID_HT_CAPABILITY:
		case WLAN_EID_HT_OPERATION:
		case WLAN_EID_VHT_CAPABILITY:
		case WLAN_EID_VHT_OPERATION:
		case WLAN_EID_MESH_ID:
		case WLAN_EID_MESH_CONFIG:
		case WLAN_EID_PEER_MGMT:
		case WLAN_EID_PREQ:
		case WLAN_EID_PREP:
		case WLAN_EID_PERR:
		case WLAN_EID_RANN:
		case WLAN_EID_CHANNEL_SWITCH:
		case WLAN_EID_EXT_CHANSWITCH_ANN:
		case WLAN_EID_COUNTRY:
		case WLAN_EID_PWR_CONSTRAINT:
		case WLAN_EID_TIMEOUT_INTERVAL:
		case WLAN_EID_SECONDARY_CHANNEL_OFFSET:
		case WLAN_EID_WIDE_BW_CHANNEL_SWITCH:
		/*
		 * not listing WLAN_EID_CHANNEL_SWITCH_WRAPPER -- it seems possible
		 * that if the content gets bigger it might be needed more than once
		 */
			if (test_bit(id, seen_elems)) {
				elems->parse_error = true;
				left -= elen;
				pos += elen;
				continue;
			}
			break;
		}

		if (calc_crc && id < 64 && (filter & (1ULL << id)))
			crc = crc32_be(crc, pos - 2, elen + 2);

		elem_parse_failed = false;

		switch (id) {
		case WLAN_EID_SSID:
			elems->ssid = pos;
			elems->ssid_len = elen;
			break;
		case WLAN_EID_SUPP_RATES:
			elems->supp_rates = pos;
			elems->supp_rates_len = elen;
			break;
		case WLAN_EID_DS_PARAMS:
			if (elen >= 1)
				elems->ds_params = pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_TIM:
			if (elen >= sizeof(struct ieee80211_tim_ie)) {
				elems->tim = (void *)pos;
				elems->tim_len = elen;
			} else
				elem_parse_failed = true;
			break;
		case WLAN_EID_CHALLENGE:
			elems->challenge = pos;
			elems->challenge_len = elen;
			break;
		case WLAN_EID_VENDOR_SPECIFIC:
			if (elen >= 4 && pos[0] == 0x00 && pos[1] == 0x50 &&
			    pos[2] == 0xf2) {
				/* Microsoft OUI (00:50:F2) */

				if (calc_crc)
					crc = crc32_be(crc, pos - 2, elen + 2);

				if (elen >= 5 && pos[3] == 2) {
					/* OUI Type 2 - WMM IE */
					if (pos[4] == 0) {
						elems->wmm_info = pos;
						elems->wmm_info_len = elen;
					} else if (pos[4] == 1) {
						elems->wmm_param = pos;
						elems->wmm_param_len = elen;
					}
				}
			}
			break;
		case WLAN_EID_RSN:
			elems->rsn = pos;
			elems->rsn_len = elen;
			break;
		case WLAN_EID_ERP_INFO:
			if (elen >= 1)
				elems->erp_info = pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_EXT_SUPP_RATES:
			elems->ext_supp_rates = pos;
			elems->ext_supp_rates_len = elen;
			break;
		case WLAN_EID_HT_CAPABILITY:
			if (elen >= sizeof(struct ieee80211_ht_cap))
				elems->ht_cap_elem = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_HT_OPERATION:
			if (elen >= sizeof(struct ieee80211_ht_operation))
				elems->ht_operation = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_VHT_CAPABILITY:
			if (elen >= sizeof(struct ieee80211_vht_cap))
				elems->vht_cap_elem = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_VHT_OPERATION:
			if (elen >= sizeof(struct ieee80211_vht_operation))
				elems->vht_operation = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_OPMODE_NOTIF:
			if (elen > 0)
				elems->opmode_notif = pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_MESH_ID:
			elems->mesh_id = pos;
			elems->mesh_id_len = elen;
			break;
		case WLAN_EID_MESH_CONFIG:
			if (elen >= sizeof(struct ieee80211_meshconf_ie))
				elems->mesh_config = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_PEER_MGMT:
			elems->peering = pos;
			elems->peering_len = elen;
			break;
		case WLAN_EID_MESH_AWAKE_WINDOW:
			if (elen >= 2)
				elems->awake_window = (void *)pos;
			break;
		case WLAN_EID_PREQ:
			elems->preq = pos;
			elems->preq_len = elen;
			break;
		case WLAN_EID_PREP:
			elems->prep = pos;
			elems->prep_len = elen;
			break;
		case WLAN_EID_PERR:
			elems->perr = pos;
			elems->perr_len = elen;
			break;
		case WLAN_EID_RANN:
			if (elen >= sizeof(struct ieee80211_rann_ie))
				elems->rann = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		case WLAN_EID_CHANNEL_SWITCH:
			if (elen != sizeof(struct ieee80211_channel_sw_ie)) {
				elem_parse_failed = true;
				break;
			}
			elems->ch_switch_ie = (void *)pos;
			break;
		case WLAN_EID_EXT_CHANSWITCH_ANN:
			if (elen != sizeof(struct ieee80211_ext_chansw_ie)) {
				elem_parse_failed = true;
				break;
			}
			elems->ext_chansw_ie = (void *)pos;
			break;
		case WLAN_EID_SECONDARY_CHANNEL_OFFSET:
			if (elen != sizeof(struct ieee80211_sec_chan_offs_ie)) {
				elem_parse_failed = true;
				break;
			}
			elems->sec_chan_offs = (void *)pos;
			break;
		case WLAN_EID_WIDE_BW_CHANNEL_SWITCH:
			if (!action ||
			    elen != sizeof(*elems->wide_bw_chansw_ie)) {
				elem_parse_failed = true;
				break;
			}
			elems->wide_bw_chansw_ie = (void *)pos;
			break;
		case WLAN_EID_CHANNEL_SWITCH_WRAPPER:
			if (action) {
				elem_parse_failed = true;
				break;
			}
			/*
			 * This is a bit tricky, but as we only care about
			 * the wide bandwidth channel switch element, so
			 * just parse it out manually.
			 */
			ie = cfg80211_find_ie(WLAN_EID_WIDE_BW_CHANNEL_SWITCH,
					      pos, elen);
			if (ie) {
				if (ie[1] == sizeof(*elems->wide_bw_chansw_ie))
					elems->wide_bw_chansw_ie =
						(void *)(ie + 2);
				else
					elem_parse_failed = true;
			}
			break;
		case WLAN_EID_COUNTRY:
			elems->country_elem = pos;
			elems->country_elem_len = elen;
			break;
		case WLAN_EID_PWR_CONSTRAINT:
			if (elen != 1) {
				elem_parse_failed = true;
				break;
			}
			elems->pwr_constr_elem = pos;
			break;
		case WLAN_EID_TIMEOUT_INTERVAL:
			if (elen >= sizeof(struct ieee80211_timeout_interval_ie))
				elems->timeout_int = (void *)pos;
			else
				elem_parse_failed = true;
			break;
		default:
			break;
		}

		if (elem_parse_failed)
			elems->parse_error = true;
		else
			__set_bit(id, seen_elems);

		left -= elen;
		pos += elen;
	}

	if (left != 0)
		elems->parse_error = true;

	return crc;
}