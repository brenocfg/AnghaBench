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
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_light_sleep_start () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int xPortGetCoreID () ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_light_sleep(void* arg)
{
    vTaskDelay(2);
    for (int i = 0; i < 1000; ++i) {
        printf("%d %d\n", xPortGetCoreID(), i);
        fflush(stdout);
        esp_light_sleep_start();
    }
    SemaphoreHandle_t done = (SemaphoreHandle_t) arg;
    xSemaphoreGive(done);
    vTaskDelete(NULL);
}