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
struct wps_data {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  network_key_len; int /*<<< orphan*/  network_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_NETWORK_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_build_cred_network_key(struct wps_data *wps, struct wpabuf *msg)
{
	wpa_printf(MSG_DEBUG,  "WPS:  * Network Key");
	wpabuf_put_be16(msg, ATTR_NETWORK_KEY);
	wpabuf_put_be16(msg, wps->wps->network_key_len);
	wpabuf_put_data(msg, wps->wps->network_key, wps->wps->network_key_len);
	return 0;
}