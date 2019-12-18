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
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */

int wpa_auth_for_each_sta(struct wpa_authenticator *wpa_auth,
              int (*cb)(struct wpa_state_machine *sm, void *ctx),
              void *cb_ctx)
{
    return 0;
}