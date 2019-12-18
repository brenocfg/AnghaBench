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
struct wps_parse_attr {scalar_t__* selected_registrar; int /*<<< orphan*/  uuid_r; int /*<<< orphan*/  authorized_macs_len; int /*<<< orphan*/  authorized_macs; int /*<<< orphan*/ * version2; int /*<<< orphan*/  sel_reg_config_methods; int /*<<< orphan*/  dev_password_id; int /*<<< orphan*/  version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (struct wps_parse_attr*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_authorized_macs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_dev_password_id (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_sel_reg_config_methods (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ wps_validate_uuid_r (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version2 (int /*<<< orphan*/ *,int) ; 

int wps_validate_upnp_set_selected_registrar(const struct wpabuf *tlvs)
{
	struct wps_parse_attr *attr;
	int wps2;
	int sel_reg;
	int ret;

	attr = (struct wps_parse_attr *)os_zalloc(sizeof(struct wps_parse_attr));
	if (attr == NULL) {
		ret = -99;
		goto _out;
	}

	if (tlvs == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No TLVs in "
			   "SetSelectedRegistrar");
		ret = -1;
		goto _out;
	}
	if (wps_parse_msg(tlvs, attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse attributes "
			   "in SetSelectedRegistrar");
		ret = -1;
		goto _out;
	}

	wps2 = attr->version2 != NULL;
	sel_reg = attr->selected_registrar != NULL &&
		*attr->selected_registrar != 0;
	if (wps_validate_version(attr->version, 1) ||
	    wps_validate_dev_password_id(attr->dev_password_id, sel_reg) ||
	    wps_validate_sel_reg_config_methods(attr->sel_reg_config_methods,
						wps2, sel_reg) ||
	    wps_validate_version2(attr->version2, wps2) ||
	    wps_validate_authorized_macs(attr->authorized_macs,
					 attr->authorized_macs_len, wps2) ||
	    wps_validate_uuid_r(attr->uuid_r, wps2)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid "
			   "SetSelectedRegistrar");
#ifdef WPS_STRICT_WPS2
		if (wps2) {
			ret = -1;
			goto _out;
		}
#else /* WPS_STRICT_WPS2 */
		ret -1;
		goto _out;
#endif /* WPS_STRICT_WPS2 */
	}

	ret = 0;
_out:
	if (attr)
		os_free(attr);

	return ret;
}