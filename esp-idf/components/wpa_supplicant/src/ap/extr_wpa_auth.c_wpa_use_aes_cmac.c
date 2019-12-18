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
struct wpa_state_machine {int /*<<< orphan*/  wpa_key_mgmt; } ;

/* Variables and functions */
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sha256 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_use_aes_cmac(struct wpa_state_machine *sm)
{
    int ret = 0;
#ifdef CONFIG_IEEE80211R
    if (wpa_key_mgmt_ft(sm->wpa_key_mgmt))
        ret = 1;
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_IEEE80211W
    if (wpa_key_mgmt_sha256(sm->wpa_key_mgmt))
        ret = 1;
#endif /* CONFIG_IEEE80211W */
    return ret;
}