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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 scalar_t__ ESP_OK ; 
 int PACKETS_NUMBER ; 
 int PACKET_READ_TICS ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  UART_NUM1 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ print_packet_data (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rs485_init () ; 
 int /*<<< orphan*/  uart_driver_delete (int /*<<< orphan*/ ) ; 
 int uart_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_wait_tx_done (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_write_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 

__attribute__((used)) static void rs485_slave(void)
{
    rs485_init();
    uint8_t* slave_data = (uint8_t*) malloc(BUF_SIZE);
    uint16_t err_count = 0, good_count = 0;
    printf("Start recieve loop.\r\n");
    unity_send_signal("Slave_ready");
    unity_wait_for_signal("Master_started");
    for(int pack_count = 0; pack_count < PACKETS_NUMBER; pack_count++) {
        //Read slave_data from UART
        int len = uart_read_bytes(UART_NUM1, slave_data, BUF_SIZE, (PACKET_READ_TICS * 2));
        //Write slave_data back to UART
        if (len > 2) {
            esp_err_t status = print_packet_data("Received ", slave_data, len);

            // If received packet is correct then send it back
            if (status == ESP_OK) {
                uart_write_bytes(UART_NUM1, (char*)slave_data, len);
                good_count++;
            } else {
                printf("Incorrect packet received.\r\n");
                err_count++;
            }
        } else {
            printf("Incorrect data packet[%d] received.\r\n", pack_count);
            err_count++;
        }
    }
    printf("Test completed. Received packets = %d, errors = %d\r\n", good_count, err_count);
    // Wait for packet to be sent
    uart_wait_tx_done(UART_NUM1, PACKET_READ_TICS);
    free(slave_data);
    uart_driver_delete(UART_NUM1);
    TEST_ASSERT(err_count < 2);
}