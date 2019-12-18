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
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void task_count(void *vp_counter)
{
    volatile unsigned *counter = (volatile unsigned *)vp_counter;
    *counter = 0;

    while (1) {
        (*counter)++;
        vTaskDelay(1);
    }
}