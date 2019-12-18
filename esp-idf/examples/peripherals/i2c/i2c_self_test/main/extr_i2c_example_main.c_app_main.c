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
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_master_init () ; 
 int /*<<< orphan*/  i2c_slave_init () ; 
 int /*<<< orphan*/  i2c_test_task ; 
 int /*<<< orphan*/  print_mux ; 
 int /*<<< orphan*/  xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,void*,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    print_mux = xSemaphoreCreateMutex();
    ESP_ERROR_CHECK(i2c_slave_init());
    ESP_ERROR_CHECK(i2c_master_init());
    xTaskCreate(i2c_test_task, "i2c_test_task_0", 1024 * 2, (void *)0, 10, NULL);
    xTaskCreate(i2c_test_task, "i2c_test_task_1", 1024 * 2, (void *)1, 10, NULL);
}