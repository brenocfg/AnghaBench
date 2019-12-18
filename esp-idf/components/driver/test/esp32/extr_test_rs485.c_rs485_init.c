#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rx_flow_ctrl_thresh; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  stop_bits; int /*<<< orphan*/  parity; int /*<<< orphan*/  data_bits; int /*<<< orphan*/  baud_rate; } ;
typedef  TYPE_1__ uart_config_t ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  UART1_RTS_PIN ; 
 int /*<<< orphan*/  UART1_RX_PIN ; 
 int /*<<< orphan*/  UART1_TX_PIN ; 
 int /*<<< orphan*/  UART_BAUD_115200 ; 
 int /*<<< orphan*/  UART_DATA_8_BITS ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_DISABLE ; 
 int /*<<< orphan*/  UART_MODE_RS485_HALF_DUPLEX ; 
 int /*<<< orphan*/  UART_NUM1 ; 
 int /*<<< orphan*/  UART_PARITY_DISABLE ; 
 int /*<<< orphan*/  UART_PIN_NO_CHANGE ; 
 int /*<<< orphan*/  UART_STOP_BITS_1 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  uart_driver_install (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_param_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uart_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_set_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs485_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
    printf("RS485 port initialization...\r\n");
    // Configure UART1 parameters
    uart_param_config(UART_NUM1, &uart_config);
    // Set UART1 pins(TX: IO4, RX: I05, RTS: IO18, CTS: IO19)
    uart_set_pin(UART_NUM1, UART1_TX_PIN, UART1_RX_PIN, UART1_RTS_PIN, UART_PIN_NO_CHANGE);
    // Install UART driver (we don't need an event queue here)
    uart_driver_install(UART_NUM1, BUF_SIZE * 2, 0, 0, NULL, 0);
    // Setup rs485 half duplex mode
    //uart_set_rs485_hd_mode(uart_num, true);
    uart_set_mode(UART_NUM1, UART_MODE_RS485_HALF_DUPLEX);
}