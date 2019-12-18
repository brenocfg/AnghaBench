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
typedef  int uart_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ GPIO_IS_VALID_GPIO (int) ; 
 scalar_t__ GPIO_IS_VALID_OUTPUT_GPIO (int) ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  GPIO_PULLUP_ONLY ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int U0CTS_IN_IDX ; 
 int U0RTS_OUT_IDX ; 
 int U0RXD_IN_IDX ; 
 int U0TXD_OUT_IDX ; 
 int U1CTS_IN_IDX ; 
 int U1RTS_OUT_IDX ; 
 int U1RXD_IN_IDX ; 
 int U1TXD_OUT_IDX ; 
 int U2CTS_IN_IDX ; 
 int U2RTS_OUT_IDX ; 
 int U2RXD_IN_IDX ; 
 int U2TXD_OUT_IDX ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
#define  UART_NUM_0 131 
#define  UART_NUM_1 130 
#define  UART_NUM_2 129 
#define  UART_NUM_MAX 128 
 int /*<<< orphan*/  gpio_matrix_in (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_out (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_direction (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_level (int,int) ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int,int /*<<< orphan*/ ) ; 

esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num, int rts_io_num, int cts_io_num)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_CHECK((tx_io_num < 0 || (GPIO_IS_VALID_OUTPUT_GPIO(tx_io_num))), "tx_io_num error", ESP_FAIL);
    UART_CHECK((rx_io_num < 0 || (GPIO_IS_VALID_GPIO(rx_io_num))), "rx_io_num error", ESP_FAIL);
    UART_CHECK((rts_io_num < 0 || (GPIO_IS_VALID_OUTPUT_GPIO(rts_io_num))), "rts_io_num error", ESP_FAIL);
    UART_CHECK((cts_io_num < 0 || (GPIO_IS_VALID_GPIO(cts_io_num))), "cts_io_num error", ESP_FAIL);

    int tx_sig, rx_sig, rts_sig, cts_sig;
    switch(uart_num) {
        case UART_NUM_0:
            tx_sig = U0TXD_OUT_IDX;
            rx_sig = U0RXD_IN_IDX;
            rts_sig = U0RTS_OUT_IDX;
            cts_sig = U0CTS_IN_IDX;
            break;
        case UART_NUM_1:
            tx_sig = U1TXD_OUT_IDX;
            rx_sig = U1RXD_IN_IDX;
            rts_sig = U1RTS_OUT_IDX;
            cts_sig = U1CTS_IN_IDX;
            break;
#if UART_NUM > 2
        case UART_NUM_2:
            tx_sig = U2TXD_OUT_IDX;
            rx_sig = U2RXD_IN_IDX;
            rts_sig = U2RTS_OUT_IDX;
            cts_sig = U2CTS_IN_IDX;
            break;
#endif
        case UART_NUM_MAX:
            default:
            tx_sig = U0TXD_OUT_IDX;
            rx_sig = U0RXD_IN_IDX;
            rts_sig = U0RTS_OUT_IDX;
            cts_sig = U0CTS_IN_IDX;
            break;
    }
    if (tx_io_num >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[tx_io_num], PIN_FUNC_GPIO);
        gpio_set_level(tx_io_num, 1);
        gpio_matrix_out(tx_io_num, tx_sig, 0, 0);
    }

    if (rx_io_num >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[rx_io_num], PIN_FUNC_GPIO);
        gpio_set_pull_mode(rx_io_num, GPIO_PULLUP_ONLY);
        gpio_set_direction(rx_io_num, GPIO_MODE_INPUT);
        gpio_matrix_in(rx_io_num, rx_sig, 0);
    }
    if (rts_io_num >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[rts_io_num], PIN_FUNC_GPIO);
        gpio_set_direction(rts_io_num, GPIO_MODE_OUTPUT);
        gpio_matrix_out(rts_io_num, rts_sig, 0, 0);
    }
    if (cts_io_num >= 0) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[cts_io_num], PIN_FUNC_GPIO);
        gpio_set_pull_mode(cts_io_num, GPIO_PULLUP_ONLY);
        gpio_set_direction(cts_io_num, GPIO_MODE_INPUT);
        gpio_matrix_in(cts_io_num, cts_sig, 0);
    }
    return ESP_OK;
}