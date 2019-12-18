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
struct wps_device_data {scalar_t__ manufacturer; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 size_t ATTR_MANUFACTURER ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,char) ; 

int wps_build_manufacturer(struct wps_device_data *dev, struct wpabuf *msg)
{
	size_t len;
	wpa_printf(MSG_DEBUG,  "WPS:  * Manufacturer");
	wpabuf_put_be16(msg, ATTR_MANUFACTURER);
	len = dev->manufacturer ? os_strlen(dev->manufacturer) : 0;
#ifndef CONFIG_WPS_STRICT
	if (len == 0) {
		/*
		 * Some deployed WPS implementations fail to parse zero-length
		 * attributes. As a workaround, send a space character if the
		 * device attribute string is empty.
		 */
		wpabuf_put_be16(msg, 1);
		wpabuf_put_u8(msg, ' ');
		return 0;
	}
#endif /* CONFIG_WPS_STRICT */
	wpabuf_put_be16(msg, len);
	wpabuf_put_data(msg, dev->manufacturer, len);
	return 0;
}