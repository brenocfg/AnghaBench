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
struct wps_parse_attr {int /*<<< orphan*/ * version2; int /*<<< orphan*/  os_version; int /*<<< orphan*/  config_error; int /*<<< orphan*/  assoc_state; int /*<<< orphan*/  rf_bands; int /*<<< orphan*/  dev_name_len; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  primary_dev_type; int /*<<< orphan*/  serial_number_len; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number_len; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name_len; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer_len; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  conn_type_flags; int /*<<< orphan*/  encr_type_flags; int /*<<< orphan*/  auth_type_flags; int /*<<< orphan*/  uuid_r; int /*<<< orphan*/  registrar_nonce; int /*<<< orphan*/  enrollee_nonce; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_assoc_state (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_auth_type_flags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_config_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_config_methods (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ wps_validate_conn_type_flags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_dev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_encr_type_flags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_enrollee_nonce (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_manufacturer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_model_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_model_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_msg_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_os_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_primary_dev_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_registrar_nonce (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_rf_bands (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_serial_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_uuid_r (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version2 (int /*<<< orphan*/ *,int) ; 

int wps_validate_m2d(const struct wpabuf *tlvs)
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
		wpa_printf(MSG_INFO, "WPS-STRICT: No TLVs in M2D");
		ret = -1;
		goto _out;
	}
	if (wps_parse_msg(tlvs, attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse attributes "
			   "in M2D");
		ret = -1;
		goto _out;
	}

	wps2 = attr->version2 != NULL;
	if (wps_validate_version(attr->version, 1) ||
	    wps_validate_msg_type(attr->msg_type, 1) ||
	    wps_validate_enrollee_nonce(attr->enrollee_nonce, 1) ||
	    wps_validate_registrar_nonce(attr->registrar_nonce, 1) ||
	    wps_validate_uuid_r(attr->uuid_r, 1) ||
	    wps_validate_auth_type_flags(attr->auth_type_flags, 1) ||
	    wps_validate_encr_type_flags(attr->encr_type_flags, 1) ||
	    wps_validate_conn_type_flags(attr->conn_type_flags, 1) ||
	    wps_validate_config_methods(attr->config_methods, wps2, 1) ||
	    wps_validate_manufacturer(attr->manufacturer, attr->manufacturer_len,
				      1) ||
	    wps_validate_model_name(attr->model_name, attr->model_name_len, 1) ||
	    wps_validate_model_number(attr->model_number, attr->model_number_len,
				      1) ||
	    wps_validate_serial_number(attr->serial_number,
				       attr->serial_number_len, 1) ||
	    wps_validate_primary_dev_type(attr->primary_dev_type, 1) ||
	    wps_validate_dev_name(attr->dev_name, attr->dev_name_len, 1) ||
	    wps_validate_rf_bands(attr->rf_bands, 1) ||
	    wps_validate_assoc_state(attr->assoc_state, 1) ||
	    wps_validate_config_error(attr->config_error, 1) ||
	    wps_validate_os_version(attr->os_version, 1) ||
	    wps_validate_version2(attr->version2, wps2)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid M2D");
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