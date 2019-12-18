#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uart_port_t ;
struct TYPE_4__ {scalar_t__ rd; scalar_t__ wr; scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ uart_pat_rb_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {TYPE_1__ rx_pattern_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  UART_CHECK (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__** p_uart_obj ; 
 int /*<<< orphan*/ * uart_spinlock ; 

__attribute__((used)) static esp_err_t uart_pattern_dequeue(uart_port_t uart_num)
{
    UART_CHECK((p_uart_obj[uart_num]), "uart driver error", ESP_FAIL);
    if (p_uart_obj[uart_num]->rx_pattern_pos.data == NULL) {
        return ESP_ERR_INVALID_STATE;
    } else {
        esp_err_t ret = ESP_OK;
        UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
        uart_pat_rb_t *p_pos = &p_uart_obj[uart_num]->rx_pattern_pos;
        if (p_pos->rd == p_pos->wr) {
            ret = ESP_FAIL;
        } else {
            p_pos->rd++;
        }
        if (p_pos->rd >= p_pos->len) {
            p_pos->rd = 0;
        }
        UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
        return ret;
    }
}