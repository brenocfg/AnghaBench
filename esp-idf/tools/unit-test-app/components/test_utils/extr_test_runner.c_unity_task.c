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
 int /*<<< orphan*/  unity_run_menu () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void unity_task(void *pvParameters)
{
    vTaskDelay(2); /* Delay a bit to let the main task be deleted */
    unity_run_menu(); /* Doesn't return */
}