#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_state_machine {scalar_t__ pairwise; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  SNonce; int /*<<< orphan*/  ANonce; int /*<<< orphan*/  addr; TYPE_1__* wpa_auth; } ;
struct wpa_ptk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMK_LEN ; 
 scalar_t__ WPA_CIPHER_TKIP ; 
 int wpa_auth_derive_ptk_ft (struct wpa_state_machine*,int /*<<< orphan*/  const*,struct wpa_ptk*,size_t) ; 
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_key_mgmt_sha256 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_pmk_to_ptk (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_derive_ptk(struct wpa_state_machine *sm, const u8 *pmk,
              struct wpa_ptk *ptk)
{
    size_t ptk_len = sm->pairwise != WPA_CIPHER_TKIP ? 48 : 64;
#ifdef CONFIG_IEEE80211R
    if (wpa_key_mgmt_ft(sm->wpa_key_mgmt))
        return wpa_auth_derive_ptk_ft(sm, pmk, ptk, ptk_len);
#endif /* CONFIG_IEEE80211R */

    wpa_pmk_to_ptk(pmk, PMK_LEN, "Pairwise key expansion",
               sm->wpa_auth->addr, sm->addr, sm->ANonce, sm->SNonce,
               (u8 *) ptk, ptk_len,
               wpa_key_mgmt_sha256(sm->wpa_key_mgmt));

    return 0;
}