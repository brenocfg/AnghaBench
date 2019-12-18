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
 int /*<<< orphan*/  UNITY_FREERTOS_CPU ; 
 scalar_t__ UNITY_FREERTOS_PRIORITY ; 
 int apb_access_corrupt ; 
 int /*<<< orphan*/  apb_access_loop_task ; 
 int /*<<< orphan*/  apb_task_handle ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 

void start_apb_access_loop(void)
{
    apb_access_corrupt = false;
    xTaskCreatePinnedToCore(apb_access_loop_task, "accessAPB", 2048, NULL,
                            UNITY_FREERTOS_PRIORITY - 1,
                            &apb_task_handle, !UNITY_FREERTOS_CPU);
}