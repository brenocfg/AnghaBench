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
 int /*<<< orphan*/  joy_close_joystick (int /*<<< orphan*/ *) ; 
 int joy_count ; 
 int /*<<< orphan*/  joy_release_joystick (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * joys ; 

void joy_release_joysticks(void)    {
    int i;

    for(i = 0; i < joy_count; ++i)  {
        joy_close_joystick(joys + i);
        joy_release_joystick(joys + i);
    }

    if(joys != NULL)    {
        free(joys);
        joys = NULL;
    }

    joy_count = 0;
}