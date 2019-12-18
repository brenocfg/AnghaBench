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
typedef  int /*<<< orphan*/  u8 ;
struct wps_credential {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wps_process_cred_eap_type(struct wps_credential *cred,
				     const u8 *eap_type, size_t eap_type_len)
{
	if (eap_type == NULL)
		return 0; /* optional attribute */

	wpa_hexdump(MSG_DEBUG, "WPS: EAP Type", eap_type, eap_type_len);

	return 0;
}