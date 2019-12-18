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
typedef  int /*<<< orphan*/ * TaskHandle_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_task_wdt_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_e (char*) ; 
 int /*<<< orphan*/ * xTaskGetIdleTaskHandleForCPU (int) ; 

void disableCore1WDT(){
    TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU(1);
    if(idle_1 == NULL || esp_task_wdt_delete(idle_1) != ESP_OK){
        log_e("Failed to remove Core 1 IDLE task from WDT");
    }
}