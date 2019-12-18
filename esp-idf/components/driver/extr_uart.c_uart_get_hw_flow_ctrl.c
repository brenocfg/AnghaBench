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
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  uart_hw_flowcontrol_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ tx_flow_en; } ;
struct TYPE_4__ {scalar_t__ rx_flow_en; } ;
struct TYPE_6__ {TYPE_2__ conf0; TYPE_1__ conf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__** UART ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_CTS ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_DISABLE ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_RTS ; 
 size_t UART_NUM_MAX ; 

esp_err_t uart_get_hw_flow_ctrl(uart_port_t uart_num, uart_hw_flowcontrol_t *flow_ctrl)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    uart_hw_flowcontrol_t val = UART_HW_FLOWCTRL_DISABLE;
    if (UART[uart_num]->conf1.rx_flow_en) {
        val |= UART_HW_FLOWCTRL_RTS;
    }
    if (UART[uart_num]->conf0.tx_flow_en) {
        val |= UART_HW_FLOWCTRL_CTS;
    }
    (*flow_ctrl) = val;
    return ESP_OK;
}