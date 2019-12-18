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
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 int UART_FIFO_LEN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void flush_stdin_stdout(void)
{
    vTaskDelay(10 / portTICK_PERIOD_MS);
    char bitbucket[UART_FIFO_LEN];
    while (fread(bitbucket, 1, UART_FIFO_LEN, stdin) > 0) {
        ;
    }
    fflush(stdout);
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);
}