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
 int /*<<< orphan*/  UNITY_FREERTOS_PRIORITY ; 
 int /*<<< orphan*/  UNITY_FREERTOS_STACK_SIZE ; 
 int /*<<< orphan*/  unity_task ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_main(void)
{
    // Note: if unpinning this task, change the way run times are calculated in
    // unity_port_esp32.c
    xTaskCreatePinnedToCore(unity_task, "unityTask", UNITY_FREERTOS_STACK_SIZE, NULL,
                            UNITY_FREERTOS_PRIORITY, NULL, UNITY_FREERTOS_CPU);
}