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
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  uart_isr_handle_t ;
typedef  int esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ETS_UART0_INTR_SOURCE ; 
 int /*<<< orphan*/  ETS_UART1_INTR_SOURCE ; 
 int /*<<< orphan*/  ETS_UART2_INTR_SOURCE ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
#define  UART_NUM_0 130 
#define  UART_NUM_1 129 
#define  UART_NUM_2 128 
 size_t UART_NUM_MAX ; 
 int esp_intr_alloc (int /*<<< orphan*/ ,int,void (*) (void*),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_isr_register(uart_port_t uart_num, void (*fn)(void *), void *arg, int intr_alloc_flags,  uart_isr_handle_t *handle)
{
    int ret;
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    switch(uart_num) {
        case UART_NUM_1:
            ret=esp_intr_alloc(ETS_UART1_INTR_SOURCE, intr_alloc_flags, fn, arg, handle);
            break;
#if UART_NUM > 2
        case UART_NUM_2:
            ret=esp_intr_alloc(ETS_UART2_INTR_SOURCE, intr_alloc_flags, fn, arg, handle);
            break;
#endif
        case UART_NUM_0:
            default:
            ret=esp_intr_alloc(ETS_UART0_INTR_SOURCE, intr_alloc_flags, fn, arg, handle);
            break;
    }
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ret;
}