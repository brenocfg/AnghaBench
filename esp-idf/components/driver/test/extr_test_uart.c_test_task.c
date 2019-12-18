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

/* Variables and functions */
 int /*<<< orphan*/  UART_NUM1 ; 
 int exit_flag ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  uart_tx_chars (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uart_wait_tx_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_task(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    char* data = (char *) malloc(256);

    while (exit_flag == false) {
        uart_tx_chars(UART_NUM1, data, 256);
        // The uart_wait_tx_done() function does not block anything if ticks_to_wait = 0.
        uart_wait_tx_done(UART_NUM1, 0);
    }

    free(data);
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}