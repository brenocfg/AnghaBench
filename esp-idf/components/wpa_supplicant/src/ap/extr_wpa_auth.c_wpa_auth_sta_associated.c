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
struct wpa_state_machine {int started; void* AuthenticationRequest; void* Init; void* ReAuthenticationRequest; int /*<<< orphan*/  key_replay; int /*<<< orphan*/  addr; scalar_t__ ft_completed; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpa; } ;
struct wpa_authenticator {TYPE_1__ conf; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  LOGGER_DEBUG ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_auth_logger (struct wpa_authenticator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int wpa_sm_step (struct wpa_state_machine*) ; 

int wpa_auth_sta_associated(struct wpa_authenticator *wpa_auth,
                struct wpa_state_machine *sm)
{
    if (wpa_auth == NULL || !wpa_auth->conf.wpa || sm == NULL)
        return -1;

#ifdef CONFIG_IEEE80211R
    if (sm->ft_completed) {
        wpa_auth_logger(wpa_auth, sm->addr, LOGGER_DEBUG,
                "FT authentication already completed - do not "
                "start 4-way handshake");
        return 0;
    }
#endif /* CONFIG_IEEE80211R */

    if (sm->started) {
        memset(&sm->key_replay, 0, sizeof(sm->key_replay));
        sm->ReAuthenticationRequest = TRUE;
        return wpa_sm_step(sm);
    }

    sm->started = 1;

    sm->Init = TRUE;
    if (wpa_sm_step(sm) == 1)
        return 1; /* should not really happen */
    sm->Init = FALSE;
    sm->AuthenticationRequest = TRUE;
    return wpa_sm_step(sm);
}