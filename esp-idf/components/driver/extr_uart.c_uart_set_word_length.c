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
typedef  scalar_t__ uart_word_length_t ;
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {scalar_t__ bit_num; } ;
struct TYPE_4__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** UART ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UART_DATA_BITS_MAX ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t UART_NUM_MAX ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_set_word_length(uart_port_t uart_num, uart_word_length_t data_bit)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_CHECK((data_bit < UART_DATA_BITS_MAX), "data bit error", ESP_FAIL);
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    UART[uart_num]->conf0.bit_num = data_bit;
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}