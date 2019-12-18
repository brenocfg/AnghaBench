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
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int active_threshold; } ;
struct TYPE_4__ {TYPE_1__ sleep_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** UART ; 
 int UART_ACTIVE_THRESHOLD_V ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int UART_MIN_WAKEUP_THRESH ; 
 size_t UART_NUM_MAX ; 

esp_err_t uart_set_wakeup_threshold(uart_port_t uart_num, int wakeup_threshold)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_ERR_INVALID_ARG);
    UART_CHECK((wakeup_threshold <= UART_ACTIVE_THRESHOLD_V &&
                wakeup_threshold > UART_MIN_WAKEUP_THRESH),
               "wakeup_threshold out of bounds", ESP_ERR_INVALID_ARG);

    UART[uart_num]->sleep_conf.active_threshold = wakeup_threshold - UART_MIN_WAKEUP_THRESH;
    return ESP_OK;
}