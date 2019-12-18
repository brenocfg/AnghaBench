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
 int /*<<< orphan*/  uart_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucUartNumber ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskSuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMbTaskHandle ; 

void vMBPortSerialClose(void)
{
    (void)vTaskSuspend(xMbTaskHandle);
    (void)vTaskDelete(xMbTaskHandle);
    ESP_ERROR_CHECK(uart_driver_delete(ucUartNumber));
}