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
struct TYPE_4__ {int rd; int wr; scalar_t__* data; int len; } ;
typedef  TYPE_1__ uart_pat_rb_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {TYPE_1__ rx_pattern_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  UART_CHECK (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__** p_uart_obj ; 
 int /*<<< orphan*/ * uart_spinlock ; 

__attribute__((used)) static esp_err_t uart_pattern_queue_update(uart_port_t uart_num, int diff_len)
{
    UART_CHECK((p_uart_obj[uart_num]), "uart driver error", ESP_FAIL);
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    uart_pat_rb_t *p_pos = &p_uart_obj[uart_num]->rx_pattern_pos;
    int rd = p_pos->rd;
    while (rd != p_pos->wr) {
        p_pos->data[rd] -= diff_len;
        int rd_rec = rd;
        rd ++;
        if (rd >= p_pos->len) {
            rd = 0;
        }
        if (p_pos->data[rd_rec] < 0) {
            p_pos->rd = rd;
        }
    }
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}