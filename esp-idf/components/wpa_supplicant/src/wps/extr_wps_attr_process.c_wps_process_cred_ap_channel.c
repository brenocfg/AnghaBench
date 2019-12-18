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
struct wps_credential {int /*<<< orphan*/  ap_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_process_cred_ap_channel(struct wps_credential *cred,
				       const u8 *ap_channel)
{
	if (ap_channel == NULL)
		return 0; /* optional attribute */

	cred->ap_channel = WPA_GET_BE16(ap_channel);
	wpa_printf(MSG_DEBUG,  "WPS: AP Channel: %u", cred->ap_channel);

	return 0;
}