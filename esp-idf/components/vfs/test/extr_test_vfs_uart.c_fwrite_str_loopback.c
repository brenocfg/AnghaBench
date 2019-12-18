#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int loopback; } ;
struct TYPE_4__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP_CONSOLE_UART_NUM ; 
 TYPE_2__ UART0 ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char const*,int,size_t,int /*<<< orphan*/ ) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uart_tx_wait_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void fwrite_str_loopback(const char* str, size_t size)
{
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);
    UART0.conf0.loopback = 1;
    fwrite(str, 1, size, stdout);
    fflush(stdout);
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);
    vTaskDelay(2 / portTICK_PERIOD_MS);
    UART0.conf0.loopback = 0;
}