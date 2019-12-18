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
 int /*<<< orphan*/  deep_sleep_task ; 
 int /*<<< orphan*/  vTaskSuspendAll () ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_deep_sleep_from_app_cpu(void)
{
    xTaskCreatePinnedToCore(&deep_sleep_task, "ds", 2048, NULL, 5, NULL, 1);

    // keep running some non-IRAM code
    vTaskSuspendAll();

    while (true) {
        ;
    }
}