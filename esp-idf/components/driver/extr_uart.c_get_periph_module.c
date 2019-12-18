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
typedef  scalar_t__ uart_port_t ;
typedef  int /*<<< orphan*/  periph_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIPH_UART0_MODULE ; 
 int /*<<< orphan*/  PERIPH_UART1_MODULE ; 
 int /*<<< orphan*/  PERIPH_UART2_MODULE ; 
 scalar_t__ UART_NUM_0 ; 
 scalar_t__ UART_NUM_1 ; 
 scalar_t__ UART_NUM_2 ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static periph_module_t get_periph_module(uart_port_t uart_num)
{
    periph_module_t periph_module = PERIPH_UART0_MODULE;
    if (uart_num == UART_NUM_0) {
        periph_module = PERIPH_UART0_MODULE;
    } else if (uart_num == UART_NUM_1) {
        periph_module = PERIPH_UART1_MODULE;
    }
#if SOC_UART_NUM > 2
    else if (uart_num == UART_NUM_2) {
        periph_module = PERIPH_UART2_MODULE;
    }
#endif
    else {
        assert(0 && "uart_num error");
    }
    return periph_module;
}