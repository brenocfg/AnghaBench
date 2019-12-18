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
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_cred_network_idx(struct wps_credential *cred,
					const u8 *idx)
{
	if (idx == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: Credential did not include "
			   "Network Index");
		return -1;
	}

	wpa_printf(MSG_DEBUG,  "WPS: Network Index: %d", *idx);

	return 0;
}