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
struct wpa_state_machine {int /*<<< orphan*/  group; struct wpa_authenticator* wpa_auth; int /*<<< orphan*/  addr; } ;
struct wpa_authenticator {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_auth_add_sm (struct wpa_state_machine*) ; 

struct wpa_state_machine * 
wpa_auth_sta_init(struct wpa_authenticator *wpa_auth, const u8 *addr)
{
    struct wpa_state_machine *sm;

    sm = (struct wpa_state_machine *)os_zalloc(sizeof(struct wpa_state_machine));
    if (sm == NULL)
        return NULL;
    memcpy(sm->addr, addr, ETH_ALEN);

    sm->wpa_auth = wpa_auth;
    sm->group = wpa_auth->group;
    wpa_auth_add_sm(sm);

    return sm;
}