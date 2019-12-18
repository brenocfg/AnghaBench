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
typedef  int /*<<< orphan*/  u8 ;
struct wps_data {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wps_state; scalar_t__ ap; } ;

/* Variables and functions */
 int ATTR_WPS_STATE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_STATE_NOT_CONFIGURED ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_build_wps_state(struct wps_data *wps, struct wpabuf *msg)
{
	u8 state;
	if (wps->wps->ap)
		state = wps->wps->wps_state;
	else
		state = WPS_STATE_NOT_CONFIGURED;
	wpa_printf(MSG_DEBUG,  "WPS:  * Wi-Fi Protected Setup State (%d)",
		   state);
	wpabuf_put_be16(msg, ATTR_WPS_STATE);
	wpabuf_put_be16(msg, 1);
	wpabuf_put_u8(msg, state);
	return 0;
}