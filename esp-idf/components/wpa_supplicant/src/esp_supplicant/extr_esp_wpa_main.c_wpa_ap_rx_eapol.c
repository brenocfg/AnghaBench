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
struct wpa_state_machine {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  wpa_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_receive (int /*<<< orphan*/ ,struct wpa_state_machine*,int /*<<< orphan*/ *,size_t) ; 

bool  wpa_ap_rx_eapol(void *hapd_data, void *sm_data, u8 *data, size_t data_len)
{
    struct hostapd_data *hapd = (struct hostapd_data *)hapd_data;
    struct wpa_state_machine *sm = (struct wpa_state_machine *)sm_data;

    if (!hapd || !sm) {
        return false;
    }

    wpa_receive(hapd->wpa_auth, sm, data, data_len);

    return true;
}