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
typedef  int uint8_t ;
struct TYPE_3__ {int rx_flow_ctrl_thresh; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  stop_bits; int /*<<< orphan*/  parity; int /*<<< orphan*/  data_bits; int /*<<< orphan*/  baud_rate; } ;
typedef  TYPE_1__ uart_config_t ;
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 int /*<<< orphan*/  BAUD_RATE ; 
 int BUF_SIZE ; 
 int /*<<< orphan*/  ECHO_TEST_CTS ; 
 int /*<<< orphan*/  ECHO_TEST_RTS ; 
 int /*<<< orphan*/  ECHO_TEST_RXD ; 
 int /*<<< orphan*/  ECHO_TEST_TXD ; 
 int ECHO_UART_PORT ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 int /*<<< orphan*/  PACKET_READ_TICS ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  UART_DATA_8_BITS ; 
 int /*<<< orphan*/  UART_HW_FLOWCTRL_DISABLE ; 
 int /*<<< orphan*/  UART_MODE_RS485_HALF_DUPLEX ; 
 int /*<<< orphan*/  UART_PARITY_DISABLE ; 
 int /*<<< orphan*/  UART_STOP_BITS_1 ; 
 int /*<<< orphan*/  esp_log_level_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  uart_driver_install (int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_param_config (int const,TYPE_1__*) ; 
 int uart_read_bytes (int const,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_set_mode (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_set_pin (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_write_bytes (int const,char const*,int) ; 

__attribute__((used)) static void echo_task(void *arg)
{
    const int uart_num = ECHO_UART_PORT;
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };
    
    // Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);
    
    ESP_LOGI(TAG, "Start RS485 application test and configure UART.");

    // Configure UART parameters
    uart_param_config(uart_num, &uart_config);
    
    ESP_LOGI(TAG, "UART set pins, mode and install driver.");
    // Set UART1 pins(TX: IO23, RX: I022, RTS: IO18, CTS: IO19)
    uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

    // Install UART driver (we don't need an event queue here)
    // In this example we don't even use a buffer for sending data.
    uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Set RS485 half duplex mode
    uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX);

    // Allocate buffers for UART
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE);

    ESP_LOGI(TAG, "UART start recieve loop.\r\n");
    uart_write_bytes(uart_num, "Start RS485 UART test.\r\n", 24);

    while(1) {
        //Read data from UART
        int len = uart_read_bytes(uart_num, data, BUF_SIZE, PACKET_READ_TICS);
        
        //Write data back to UART
        if (len > 0) {
            uart_write_bytes(uart_num, "\r\n", 2);
            char prefix[] = "RS485 Received: [";
            uart_write_bytes(uart_num, prefix, (sizeof(prefix) - 1));
            
            ESP_LOGI(TAG, "Received %u bytes:", len);
            printf("[ ");
            for (int i = 0; i < len; i++) {
                printf("0x%.2X ", (uint8_t)data[i]);
                uart_write_bytes(uart_num, (const char*)&data[i], 1);
                // Add a Newline character if you get a return charater from paste (Paste tests multibyte receipt/buffer)
                if (data[i] == '\r') {
                    uart_write_bytes(uart_num, "\n", 1);
                }
            }
            printf("] \n");
            uart_write_bytes(uart_num, "]\r\n", 3);
        } else {
            // Echo a "." to show we are alive while we wait for input
            uart_write_bytes(uart_num, ".", 1);
        }
    }
}