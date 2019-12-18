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
typedef  int /*<<< orphan*/  u16 ;
struct wps_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_assoc_state(struct wps_data *wps, const u8 *assoc)
{
	u16 a;

	if (assoc == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Association State received");
		return -1;
	}

	a = WPA_GET_BE16(assoc);
	wpa_printf(MSG_DEBUG,  "WPS: Enrollee Association State %d", a);

	return 0;
}