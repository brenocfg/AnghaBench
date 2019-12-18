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
struct wps_parse_attr {int /*<<< orphan*/  ap_channel; int /*<<< orphan*/  dot1x_enabled; int /*<<< orphan*/  key_prov_auto; int /*<<< orphan*/  eap_identity_len; int /*<<< orphan*/  eap_identity; int /*<<< orphan*/  eap_type_len; int /*<<< orphan*/  eap_type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  network_key_len; int /*<<< orphan*/  network_key; int /*<<< orphan*/  network_key_idx; int /*<<< orphan*/  encr_type; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  network_idx; } ;
struct wps_credential {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_process_cred_802_1x_enabled (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_ap_channel (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_auth_type (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_eap_identity (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_eap_type (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_encr_type (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_key_prov_auto (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_mac_addr (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_idx (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_key (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_network_key_idx (struct wps_credential*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_cred_ssid (struct wps_credential*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wps_workaround_cred_key (struct wps_credential*) ; 

int wps_process_cred(struct wps_parse_attr *attr,
		     struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG,  "WPS: Process Credential");

	/* TODO: support multiple Network Keys */
	if (wps_process_cred_network_idx(cred, attr->network_idx) ||
	    wps_process_cred_ssid(cred, attr->ssid, attr->ssid_len) ||
	    wps_process_cred_auth_type(cred, attr->auth_type) ||
	    wps_process_cred_encr_type(cred, attr->encr_type) ||
	    wps_process_cred_network_key_idx(cred, attr->network_key_idx) ||
	    wps_process_cred_network_key(cred, attr->network_key,
					 attr->network_key_len) ||
	    wps_process_cred_mac_addr(cred, attr->mac_addr) ||
	    wps_process_cred_eap_type(cred, attr->eap_type,
				      attr->eap_type_len) ||
	    wps_process_cred_eap_identity(cred, attr->eap_identity,
					  attr->eap_identity_len) ||
	    wps_process_cred_key_prov_auto(cred, attr->key_prov_auto) ||
	    wps_process_cred_802_1x_enabled(cred, attr->dot1x_enabled) ||
	    wps_process_cred_ap_channel(cred, attr->ap_channel))
		return -1;

	return wps_workaround_cred_key(cred);
}