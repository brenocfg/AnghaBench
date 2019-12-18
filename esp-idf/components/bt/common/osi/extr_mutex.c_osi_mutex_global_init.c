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
 int /*<<< orphan*/ * gl_mutex ; 
 int /*<<< orphan*/ * xSemaphoreCreateRecursiveMutex () ; 

int osi_mutex_global_init(void)
{
    gl_mutex = xSemaphoreCreateRecursiveMutex();
    if (gl_mutex == NULL) {
        return -1;
    }

    return 0;
}