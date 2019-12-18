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
struct wpa_state_machine {int /*<<< orphan*/  TimeoutEvt; scalar_t__ pending_1_of_4_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpa_sm_step (struct wpa_state_machine*) ; 

__attribute__((used)) static void wpa_send_eapol_timeout(void *eloop_ctx, void *timeout_ctx)
{
    struct wpa_state_machine *sm = timeout_ctx;

    sm->pending_1_of_4_timeout = 0;
    sm->TimeoutEvt = TRUE;
    wpa_sm_step(sm);
}