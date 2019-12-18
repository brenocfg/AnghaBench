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
struct wps_device_data {int /*<<< orphan*/  pri_dev_type; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PRIMARY_DEV_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_DEV_TYPE_LEN ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wps_build_primary_dev_type(struct wps_device_data *dev, struct wpabuf *msg)
{
	wpa_printf(MSG_DEBUG,  "WPS:  * Primary Device Type");
	wpabuf_put_be16(msg, ATTR_PRIMARY_DEV_TYPE);
	wpabuf_put_be16(msg, WPS_DEV_TYPE_LEN);
	wpabuf_put_data(msg, dev->pri_dev_type, WPS_DEV_TYPE_LEN);
	return 0;
}