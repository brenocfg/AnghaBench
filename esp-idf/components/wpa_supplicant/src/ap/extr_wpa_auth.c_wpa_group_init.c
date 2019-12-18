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
struct wpa_group {void* GInit; int /*<<< orphan*/  GTK_len; void* GTKAuthenticator; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpa_group; } ;
struct wpa_authenticator {TYPE_1__ conf; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 int /*<<< orphan*/  os_free (struct wpa_group*) ; 
 scalar_t__ os_zalloc (int) ; 
 int random_pool_ready () ; 
 int /*<<< orphan*/  wpa_cipher_key_len (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_group_init_gmk_and_counter (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_sm_step (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpa_group * wpa_group_init(struct wpa_authenticator *wpa_auth,
                     int vlan_id, int delay_init)
{
    struct wpa_group *group;
    group = (struct wpa_group *)os_zalloc(sizeof(struct wpa_group));
    if (group == NULL)
        return NULL;

    group->GTKAuthenticator = TRUE;
    group->GTK_len = wpa_cipher_key_len(wpa_auth->conf.wpa_group);

    if (random_pool_ready() != 1) {
        wpa_printf( MSG_INFO, "WPA: Not enough entropy in random pool "
               "for secure operations - update keys later when "
               "the first station connects");
    }

    /*
     * Set initial GMK/Counter value here. The actual values that will be
     * used in negotiations will be set once the first station tries to
     * connect. This allows more time for collecting additional randomness
     * on embedded devices.
     */
    if (wpa_group_init_gmk_and_counter(wpa_auth, group) < 0) {
        wpa_printf( MSG_ERROR, "Failed to get random data for WPA "
               "initialization.");
        os_free(group);
        return NULL;
    }

    group->GInit = TRUE;
    if (delay_init) {
        wpa_printf( MSG_DEBUG, "WPA: Delay group state machine start "
               "until Beacon frames have been configured\n");
        /* Initialization is completed in wpa_init_keys(). */
    } else {
        wpa_group_sm_step(wpa_auth, group);
        group->GInit = FALSE;
        wpa_group_sm_step(wpa_auth, group);
    }

    return group;
}