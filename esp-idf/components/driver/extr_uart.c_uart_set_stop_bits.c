#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uart_stop_bits_t ;
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {scalar_t__ stop_bit_num; } ;
struct TYPE_5__ {int dl1_en; } ;
struct TYPE_6__ {TYPE_1__ conf0; TYPE_2__ rs485_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__** UART ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t UART_NUM_MAX ; 
 scalar_t__ UART_STOP_BITS_1 ; 
 scalar_t__ UART_STOP_BITS_2 ; 
 scalar_t__ UART_STOP_BITS_MAX ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_set_stop_bits(uart_port_t uart_num, uart_stop_bits_t stop_bit)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_CHECK((stop_bit < UART_STOP_BITS_MAX), "stop bit error", ESP_FAIL);

    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
#if CONFIG_IDF_TARGET_ESP32
    //workaround for hardware bug, when uart stop bit set as 2-bit mode.
    if (stop_bit == UART_STOP_BITS_2) {
        stop_bit = UART_STOP_BITS_1;
        UART[uart_num]->rs485_conf.dl1_en = 1;
    } else {
        UART[uart_num]->rs485_conf.dl1_en = 0;
    }
#endif
    UART[uart_num]->conf0.stop_bit_num = stop_bit;
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}