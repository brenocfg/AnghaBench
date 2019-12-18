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
struct wps_credential {int encr_type; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_ENCR_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_cred_encr_type(struct wpabuf *msg,
				    const struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG,  "WPS:  * Encryption Type (0x%x)",
		   cred->encr_type);
	wpabuf_put_be16(msg, ATTR_ENCR_TYPE);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, cred->encr_type);
	return 0;
}