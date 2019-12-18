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
 int /*<<< orphan*/  esp_task_wdt_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_task_wdt_init (int,int) ; 
 int /*<<< orphan*/  setup_values () ; 
 int /*<<< orphan*/  xTaskGetIdleTaskHandleForCPU (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_task_wdt(void)
{
    setup_values();
    esp_task_wdt_init(1, true);
    esp_task_wdt_add(xTaskGetIdleTaskHandleForCPU(0));
    while(1);
}