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
typedef  int u16 ;
struct wps_data {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_ENCR_TYPE_FLAGS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_ENCR_TYPES ; 
 int WPS_ENCR_WEP ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

int wps_build_encr_type_flags(struct wps_data *wps, struct wpabuf *msg)
{
	u16 encr_types = WPS_ENCR_TYPES;
#ifdef CONFIG_WPS2
	encr_types &= ~WPS_ENCR_WEP;
#endif /* CONFIG_WPS2 */
	wpa_printf(MSG_DEBUG,  "WPS:  * Encryption Type Flags");
	wpabuf_put_be16(msg, ATTR_ENCR_TYPE_FLAGS);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, encr_types);
	return 0;
}