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
struct wps_data {int /*<<< orphan*/  state; int /*<<< orphan*/  dev_password_len; int /*<<< orphan*/ * dev_password; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M4 ; 
 int /*<<< orphan*/  WPS_M3 ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_authenticator (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_e_hash (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_registrar_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_derive_psk (struct wps_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * wps_build_m3(struct wps_data *wps)
{
	struct wpabuf *msg;

	wpa_printf(MSG_DEBUG,  "WPS: Building Message M3");

	if (wps->dev_password == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Device Password available");
		return NULL;
	}
	wps_derive_psk(wps, wps->dev_password, wps->dev_password_len);

	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M3) ||
	    wps_build_registrar_nonce(wps, msg) ||
	    wps_build_e_hash(wps, msg) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0) ||
	    wps_build_authenticator(wps, msg)) {
		wpabuf_free(msg);
		return NULL;
	}

	wps->state = RECV_M4;
	return msg;
}