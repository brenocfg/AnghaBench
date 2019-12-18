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
struct wps_parse_attr {int /*<<< orphan*/  key_wrap_auth; int /*<<< orphan*/  encr_type; int /*<<< orphan*/  network_key_len; int /*<<< orphan*/  network_key; int /*<<< orphan*/  network_key_idx; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  e_snonce2; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_auth_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_e_snonce2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_encr_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_key_wrap_auth (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_mac_addr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_network_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_network_key_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_ssid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int wps_validate_m7_encr(const struct wpabuf *tlvs, int ap, int wps2)
{
	struct wps_parse_attr *attr;
	int ret;

	attr = (struct wps_parse_attr *)os_zalloc(sizeof(struct wps_parse_attr));
	if (attr == NULL) {
		ret = -99;
		goto _out;
	}
	
	if (tlvs == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No TLVs in M7 encrypted "
			   "settings");
		ret = -1;
		goto _out;
	}
	if (wps_parse_msg(tlvs, attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse attributes "
			   "in M7 encrypted settings");
		ret = -1;
		goto _out;
	}

	if (wps_validate_e_snonce2(attr->e_snonce2, 1) ||
	    wps_validate_ssid(attr->ssid, attr->ssid_len, !ap) ||
	    wps_validate_mac_addr(attr->mac_addr, !ap) ||
	    wps_validate_auth_type(attr->auth_type, !ap) ||
	    wps_validate_encr_type(attr->encr_type, !ap) ||
	    wps_validate_network_key_index(attr->network_key_idx, 0) ||
	    wps_validate_network_key(attr->network_key, attr->network_key_len,
				     attr->encr_type, !ap) ||
	    wps_validate_key_wrap_auth(attr->key_wrap_auth, 1)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid M7 encrypted "
			   "settings");
#ifdef WPS_STRICT_WPS2
		if (wps2) {
			ret = -1;
			goto _out;
		}
#else /* WPS_STRICT_WPS2 */
		ret = -1;
		goto _out;
#endif /* WPS_STRICT_WPS2 */
	}

	ret = 0;
_out:
	if (attr)
		os_free(attr);

	return ret;
}