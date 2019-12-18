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
struct wps_data {int /*<<< orphan*/  peer_hash2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_HASH_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_process_e_hash2(struct wps_data *wps, const u8 *e_hash2)
{
	if (e_hash2 == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No E-Hash2 received");
		return -1;
	}

	os_memcpy(wps->peer_hash2, e_hash2, WPS_HASH_LEN);
	wpa_hexdump(MSG_DEBUG, "WPS: E-Hash2", wps->peer_hash2, WPS_HASH_LEN);

	return 0;
}