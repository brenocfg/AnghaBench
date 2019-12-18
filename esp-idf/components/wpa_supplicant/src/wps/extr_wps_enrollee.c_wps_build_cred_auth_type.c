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
typedef  int u16 ;
struct wps_data {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int auth_types; } ;

/* Variables and functions */
 int ATTR_AUTH_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_AUTH_SHARED ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int WPS_WIFI_AUTH_OPEN ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_cred_auth_type(struct wps_data *wps, struct wpabuf *msg)
{
	u16 auth_type = wps->wps->auth_types;

	/* Select the best authentication type */
	if (auth_type & WPS_AUTH_WPA2PSK)
		auth_type = WPS_AUTH_WPA2PSK;
	else if (auth_type & WPS_AUTH_WPAPSK)
		auth_type = WPS_AUTH_WPAPSK;
	else if (auth_type & WPS_WIFI_AUTH_OPEN)
		auth_type = WPS_WIFI_AUTH_OPEN;
	else if (auth_type & WPS_AUTH_SHARED)
		auth_type = WPS_AUTH_SHARED;

	wpa_printf(MSG_DEBUG,  "WPS:  * Authentication Type (0x%x)", auth_type);
	wpabuf_put_be16(msg, ATTR_AUTH_TYPE);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, auth_type);
	return 0;
}