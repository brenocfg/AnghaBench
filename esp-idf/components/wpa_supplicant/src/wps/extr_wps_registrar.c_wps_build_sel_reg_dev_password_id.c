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
struct wps_registrar {scalar_t__ sel_reg_dev_password_id_override; int /*<<< orphan*/  sel_reg_union; scalar_t__ pbc; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_DEV_PASSWORD_ID ; 
 int DEV_PW_DEFAULT ; 
 int DEV_PW_PUSHBUTTON ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_sel_reg_dev_password_id(struct wps_registrar *reg,
					     struct wpabuf *msg)
{
	u16 id = reg->pbc ? DEV_PW_PUSHBUTTON : DEV_PW_DEFAULT;
	if (!reg->sel_reg_union)
		return 0;
	if (reg->sel_reg_dev_password_id_override >= 0)
		id = reg->sel_reg_dev_password_id_override;
	wpa_printf(MSG_DEBUG,  "WPS:  * Device Password ID (%d)", id);
	wpabuf_put_be16(msg, ATTR_DEV_PASSWORD_ID);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, id);
	return 0;
}