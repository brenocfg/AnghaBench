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
struct wps_device_data {int os_version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_OS_VERSION ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int) ; 

int wps_build_os_version(struct wps_device_data *dev, struct wpabuf *msg)
{
	wpa_printf(MSG_DEBUG,  "WPS:  * OS Version");
	wpabuf_put_be16(msg, ATTR_OS_VERSION);
	wpabuf_put_be16(msg, 4);
	wpabuf_put_be32(msg, 0x80000000 | dev->os_version);
	return 0;
}