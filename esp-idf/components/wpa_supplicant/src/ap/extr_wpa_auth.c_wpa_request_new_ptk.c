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
struct wpa_state_machine {scalar_t__ PTK_valid; int /*<<< orphan*/  PTKRequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void wpa_request_new_ptk(struct wpa_state_machine *sm)
{
    if (sm == NULL)
        return;

    sm->PTKRequest = TRUE;
    sm->PTK_valid = 0;
}