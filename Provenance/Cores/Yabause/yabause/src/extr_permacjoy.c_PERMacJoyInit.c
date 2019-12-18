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
typedef  int /*<<< orphan*/  joydata_t ;

/* Variables and functions */
 int initted ; 
 int /*<<< orphan*/ * joy_get_joystick (int) ; 
 int /*<<< orphan*/  joy_open_joystick (int /*<<< orphan*/ *) ; 
 int joy_scan_joysticks () ; 
 int joycount ; 
 int /*<<< orphan*/ ** joys ; 
 scalar_t__ malloc (int) ; 

int PERMacJoyInit(void) {
    int i;

    /* Don't bother trying to init the thing again. */
    if(initted)
        return 0;

    /* Grab the number of joysticks connected to the system. */
    joycount = joy_scan_joysticks();
    if(joycount == -1)  {
        joycount = 0;
        return -1;
    }

    joys = (joydata_t **)malloc(sizeof(joydata_t *) * joycount);
    if(!joys)   {
        joycount = 0;
        return -1;
    }

    /* Grab each joystick and open it. */
    for(i = 0; i < joycount; ++i)   {
        joys[i] = joy_get_joystick(i);

        if(joys[i] == NULL)
            continue;

        if(!joy_open_joystick(joys[i])) {
            joys[i] = NULL;
            continue;
        }
    }

    initted = 1;

    return 0;
}