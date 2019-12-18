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
 int joy_count ; 
 int /*<<< orphan*/ * joys ; 

joydata_t *joy_get_joystick(int index)  {
    if(index < 0 || index >= joy_count) {
        return NULL;
    }

    return &joys[index];
}