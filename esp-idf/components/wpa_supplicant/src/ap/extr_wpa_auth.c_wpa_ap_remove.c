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
struct wpa_state_machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_auth_sta_deinit (struct wpa_state_machine*) ; 

bool wpa_ap_remove(void* sm)
{
    struct wpa_state_machine   *wpa_sm;
    if (!sm) return false;

    wpa_sm = (struct wpa_state_machine*)sm;
    wpa_auth_sta_deinit(wpa_sm);

    return true;
}