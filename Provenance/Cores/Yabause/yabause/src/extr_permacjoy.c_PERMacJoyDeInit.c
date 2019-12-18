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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ initted ; 
 int /*<<< orphan*/  joy_close_joystick (int /*<<< orphan*/ ) ; 
 int joycount ; 
 int /*<<< orphan*/ * joys ; 

void PERMacJoyDeInit(void)  {
    int i;

    if(!initted)
        return;

    /* Close each joystick. */
    for(i = 0; i < joycount; ++i)   {
        joy_close_joystick(joys[i]);
    }

    free(joys);
    joys = NULL;
    joycount = 0;
    initted = 0;
}