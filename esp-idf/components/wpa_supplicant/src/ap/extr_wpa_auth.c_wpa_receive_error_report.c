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
struct wpa_state_machine {scalar_t__ pairwise; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ wpa_group; } ;
struct wpa_authenticator {TYPE_1__ conf; } ;

/* Variables and functions */
 scalar_t__ WPA_CIPHER_TKIP ; 
 scalar_t__ wpa_auth_mic_failure_report (struct wpa_authenticator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_request_new_ptk (struct wpa_state_machine*) ; 

__attribute__((used)) static int wpa_receive_error_report(struct wpa_authenticator *wpa_auth,
                    struct wpa_state_machine *sm, int group)
{
    if (group && wpa_auth->conf.wpa_group != WPA_CIPHER_TKIP) {
    } else if (!group && sm->pairwise != WPA_CIPHER_TKIP) {
    } else {
        if (wpa_auth_mic_failure_report(wpa_auth, sm->addr) > 0)
            return 1; /* STA entry was removed */
    }

    /*
     * Error report is not a request for a new key handshake, but since
     * Authenticator may do it, let's change the keys now anyway.
     */
    wpa_request_new_ptk(sm);
    return 0;
}