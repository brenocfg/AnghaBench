#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wps_data {int /*<<< orphan*/  state; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_ACK ; 
 int /*<<< orphan*/  WPS_FINISHED ; 
 int /*<<< orphan*/  WPS_WSC_DONE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_enrollee_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_registrar_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_success_event (TYPE_1__*) ; 

__attribute__((used)) static struct wpabuf * wps_build_wsc_done(struct wps_data *wps)
{
	struct wpabuf *msg;

	wpa_printf(MSG_DEBUG,  "WPS: Building Message WSC_Done");

	msg = wpabuf_alloc(1000);
	if (msg == NULL)
		return NULL;

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_WSC_DONE) ||
	    wps_build_enrollee_nonce(wps, msg) ||
	    wps_build_registrar_nonce(wps, msg) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0)) {
		wpabuf_free(msg);
		return NULL;
	}

	if (wps->wps->ap)
		wps->state = RECV_ACK;
	else {
		wps_success_event(wps->wps);
		wps->state = WPS_FINISHED;
	}
	return msg;
}