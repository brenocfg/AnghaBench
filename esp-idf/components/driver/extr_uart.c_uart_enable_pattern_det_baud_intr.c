#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  size_t uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_9__ {int pre_idle_num; } ;
struct TYPE_8__ {int post_idle_num; } ;
struct TYPE_7__ {int rx_gap_tout; } ;
struct TYPE_6__ {char data; int /*<<< orphan*/  char_num; } ;
struct TYPE_10__ {TYPE_4__ at_cmd_precnt; TYPE_3__ at_cmd_postcnt; TYPE_2__ at_cmd_gaptout; TYPE_1__ at_cmd_char; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 TYPE_5__** UART ; 
 int /*<<< orphan*/  UART_AT_CMD_CHAR_DET_INT_ENA_M ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 size_t UART_NUM_MAX ; 
 int UART_POST_IDLE_NUM_V ; 
 int UART_PRE_IDLE_NUM_V ; 
 int UART_RX_GAP_TOUT_V ; 
 int esp_clk_apb_freq () ; 
 int /*<<< orphan*/  uart_enable_intr_mask (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_get_baudrate (size_t,int*) ; 

esp_err_t uart_enable_pattern_det_baud_intr(uart_port_t uart_num, char pattern_chr, uint8_t chr_num, int chr_tout, int post_idle, int pre_idle)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_CHECK(chr_tout >= 0 && chr_tout <= UART_RX_GAP_TOUT_V, "uart pattern set error\n", ESP_FAIL);
    UART_CHECK(post_idle >= 0 && post_idle <= UART_POST_IDLE_NUM_V, "uart pattern set error\n", ESP_FAIL);
    UART_CHECK(pre_idle >= 0 && pre_idle <= UART_PRE_IDLE_NUM_V, "uart pattern set error\n", ESP_FAIL);
    UART[uart_num]->at_cmd_char.data = pattern_chr;
    UART[uart_num]->at_cmd_char.char_num = chr_num;

#if CONFIG_IDF_TARGET_ESP32
    int apb_clk_freq = 0;
    uint32_t uart_baud = 0;
    uint32_t uart_div = 0;

    uart_get_baudrate(uart_num, &uart_baud);
    apb_clk_freq = esp_clk_apb_freq();
    uart_div = apb_clk_freq / uart_baud;

    UART[uart_num]->at_cmd_gaptout.rx_gap_tout = chr_tout * uart_div;
    UART[uart_num]->at_cmd_postcnt.post_idle_num = post_idle * uart_div;
    UART[uart_num]->at_cmd_precnt.pre_idle_num = pre_idle * uart_div;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    UART[uart_num]->at_cmd_gaptout.rx_gap_tout = chr_tout;
    UART[uart_num]->at_cmd_postcnt.post_idle_num = post_idle;
    UART[uart_num]->at_cmd_precnt.pre_idle_num = pre_idle;
#endif

    return uart_enable_intr_mask(uart_num, UART_AT_CMD_CHAR_DET_INT_ENA_M);
}