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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DATE_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ apb_counter ; 
 int apb_test_result ; 
 int exit_flag ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accessAPB_measure_performance(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    uint32_t uart_date = REG_READ(UART_DATE_REG(0));

    apb_test_result = true;
    apb_counter = 0;
    // although exit flag is set in another task, checking (exit_flag == false) is safe
    while (exit_flag == false) {
        ++apb_counter;
        if (uart_date != REG_READ(UART_DATE_REG(0))) {
            apb_test_result = false;
            break;
        }
    }

    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}