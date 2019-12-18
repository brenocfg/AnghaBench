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
struct wpa_group {scalar_t__ changed; int /*<<< orphan*/  GTKReKey; struct wpa_group* next; } ;
struct TYPE_2__ {scalar_t__ wpa_group_rekey; } ;
struct wpa_authenticator {TYPE_1__ conf; struct wpa_group* group; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,void (*) (void*,void*),struct wpa_authenticator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_group_sm_step (struct wpa_authenticator*,struct wpa_group*) ; 

__attribute__((used)) static void wpa_rekey_gtk(void *eloop_ctx, void *timeout_ctx)
{
    struct wpa_authenticator *wpa_auth = eloop_ctx;
    struct wpa_group *group;

    for (group = wpa_auth->group; group; group = group->next) {
        group->GTKReKey = TRUE;
        do {
            group->changed = FALSE;
            wpa_group_sm_step(wpa_auth, group);
        } while (group->changed);
    }

    if (wpa_auth->conf.wpa_group_rekey) {
        eloop_register_timeout(wpa_auth->conf.wpa_group_rekey,
                       0, wpa_rekey_gtk, wpa_auth, NULL);
    }
}