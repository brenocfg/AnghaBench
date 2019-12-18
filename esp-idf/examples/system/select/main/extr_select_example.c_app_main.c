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
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  select_task ; 
 int /*<<< orphan*/  socket_write_task ; 
 int /*<<< orphan*/  uart1_write_task ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    xTaskCreate(uart1_write_task, "uart1_write_task", 4*1024, NULL, 5, NULL);
    xTaskCreate(socket_write_task, "socket_write_task", 4*1024, NULL, 5, NULL);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(select_task, "select_task", 4*1024, NULL, 5, NULL);
}