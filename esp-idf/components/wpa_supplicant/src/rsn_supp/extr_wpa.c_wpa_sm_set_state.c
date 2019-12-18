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
struct wpa_sm {int wpa_state; int /*<<< orphan*/  cm_timer; } ;
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;

/* Variables and functions */
 scalar_t__ WPA_MIC_FAILURE ; 
 scalar_t__ WPA_SM_STATE (struct wpa_sm*) ; 
 int /*<<< orphan*/  ets_timer_disarm (int /*<<< orphan*/ *) ; 
 struct wpa_sm gWpaSm ; 

void wpa_sm_set_state(enum wpa_states state)
{
       struct wpa_sm *sm = &gWpaSm;
    if(WPA_MIC_FAILURE==WPA_SM_STATE(sm))
        ets_timer_disarm(&(sm->cm_timer));
    sm->wpa_state= state;
}