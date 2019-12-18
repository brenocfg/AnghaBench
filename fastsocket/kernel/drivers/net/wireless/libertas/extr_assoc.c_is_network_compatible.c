#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {scalar_t__ WPA2enabled; scalar_t__ WPAenabled; scalar_t__ wep_enabled; } ;
struct lbs_private {TYPE_1__ secinfo; } ;
struct bss_descriptor {scalar_t__ mode; int capability; int /*<<< orphan*/ * rsn_ie; int /*<<< orphan*/ * wpa_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_SCAN ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_scan (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int match_bss_dynamic_wep (TYPE_1__*,struct bss_descriptor*) ; 
 int match_bss_no_security (TYPE_1__*,struct bss_descriptor*) ; 
 int match_bss_static_wep (TYPE_1__*,struct bss_descriptor*) ; 
 int match_bss_wpa (TYPE_1__*,struct bss_descriptor*) ; 
 int match_bss_wpa2 (TYPE_1__*,struct bss_descriptor*) ; 

__attribute__((used)) static int is_network_compatible(struct lbs_private *priv,
				 struct bss_descriptor *bss, uint8_t mode)
{
	int matched = 0;

	lbs_deb_enter(LBS_DEB_SCAN);

	if (bss->mode != mode)
		goto done;

	matched = match_bss_no_security(&priv->secinfo, bss);
	if (matched)
		goto done;
	matched = match_bss_static_wep(&priv->secinfo, bss);
	if (matched)
		goto done;
	matched = match_bss_wpa(&priv->secinfo, bss);
	if (matched) {
		lbs_deb_scan("is_network_compatible() WPA: wpa_ie 0x%x "
			     "wpa2_ie 0x%x WEP %s WPA %s WPA2 %s "
			     "privacy 0x%x\n", bss->wpa_ie[0], bss->rsn_ie[0],
			     priv->secinfo.wep_enabled ? "e" : "d",
			     priv->secinfo.WPAenabled ? "e" : "d",
			     priv->secinfo.WPA2enabled ? "e" : "d",
			     (bss->capability & WLAN_CAPABILITY_PRIVACY));
		goto done;
	}
	matched = match_bss_wpa2(&priv->secinfo, bss);
	if (matched) {
		lbs_deb_scan("is_network_compatible() WPA2: wpa_ie 0x%x "
			     "wpa2_ie 0x%x WEP %s WPA %s WPA2 %s "
			     "privacy 0x%x\n", bss->wpa_ie[0], bss->rsn_ie[0],
			     priv->secinfo.wep_enabled ? "e" : "d",
			     priv->secinfo.WPAenabled ? "e" : "d",
			     priv->secinfo.WPA2enabled ? "e" : "d",
			     (bss->capability & WLAN_CAPABILITY_PRIVACY));
		goto done;
	}
	matched = match_bss_dynamic_wep(&priv->secinfo, bss);
	if (matched) {
		lbs_deb_scan("is_network_compatible() dynamic WEP: "
			     "wpa_ie 0x%x wpa2_ie 0x%x privacy 0x%x\n",
			     bss->wpa_ie[0], bss->rsn_ie[0],
			     (bss->capability & WLAN_CAPABILITY_PRIVACY));
		goto done;
	}

	/* bss security settings don't match those configured on card */
	lbs_deb_scan("is_network_compatible() FAILED: wpa_ie 0x%x "
		     "wpa2_ie 0x%x WEP %s WPA %s WPA2 %s privacy 0x%x\n",
		     bss->wpa_ie[0], bss->rsn_ie[0],
		     priv->secinfo.wep_enabled ? "e" : "d",
		     priv->secinfo.WPAenabled ? "e" : "d",
		     priv->secinfo.WPA2enabled ? "e" : "d",
		     (bss->capability & WLAN_CAPABILITY_PRIVACY));

done:
	lbs_deb_leave_args(LBS_DEB_SCAN, "matched: %d", matched);
	return matched;
}