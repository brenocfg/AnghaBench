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
struct wps_parse_attr {int /*<<< orphan*/  authenticator; int /*<<< orphan*/ * version2; int /*<<< orphan*/  encr_settings_len; int /*<<< orphan*/  encr_settings; int /*<<< orphan*/  registrar_nonce; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_authenticator (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_encr_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_msg_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_registrar_nonce (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version2 (int /*<<< orphan*/ *,int) ; 

int wps_validate_m5(const struct wpabuf *tlvs)
{
	struct wps_parse_attr *attr;
	int wps2;
	int ret;

	attr = (struct wps_parse_attr *)os_zalloc(sizeof(struct wps_parse_attr));
	if (attr == NULL) {
		ret = -99;
		goto _out;
	}

	if (tlvs == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No TLVs in M5");
		ret = -1;
		goto _out;
	}
	if (wps_parse_msg(tlvs, attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse attributes "
			   "in M5");
		ret = -1;
		goto _out;
	}

	wps2 = attr->version2 != NULL;
	if (wps_validate_version(attr->version, 1) ||
	    wps_validate_msg_type(attr->msg_type, 1) ||
	    wps_validate_registrar_nonce(attr->registrar_nonce, 1) ||
	    wps_validate_encr_settings(attr->encr_settings,
				       attr->encr_settings_len, 1) ||
	    wps_validate_version2(attr->version2, wps2) ||
	    wps_validate_authenticator(attr->authenticator, 1)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid M5");
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