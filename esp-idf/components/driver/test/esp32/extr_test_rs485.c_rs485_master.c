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
 int BUF_SIZE ; 
 scalar_t__ ESP_OK ; 
 int PACKETS_NUMBER ; 
 int PACKET_READ_TICS ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  UART_NUM1 ; 
 int /*<<< orphan*/  buffer_fill_random (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ print_packet_data (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rs485_init () ; 
 int /*<<< orphan*/  uart_driver_delete (int /*<<< orphan*/ ) ; 
 int uart_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uart_write_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  unity_wait_for_signal (char*) ; 

__attribute__((used)) static void rs485_master(void)
{
    uint16_t err_count = 0, good_count = 0;
    rs485_init();
    uint8_t* master_buffer = (uint8_t*) malloc(BUF_SIZE);
    uint8_t* slave_buffer = (uint8_t*) malloc(BUF_SIZE);
    // The master test case should be synchronized with slave
    unity_wait_for_signal("Slave_ready");
    unity_send_signal("Master_started");
    printf("Start recieve loop.\r\n");
    for(int i = 0; i < PACKETS_NUMBER; i++) {
        // Form random buffer with CRC16
        buffer_fill_random(master_buffer, BUF_SIZE);
        // Print created packet for debugging
        esp_err_t status = print_packet_data("Send ", master_buffer, BUF_SIZE);
        TEST_ASSERT(status == ESP_OK);
        uart_write_bytes(UART_NUM1, (char*)master_buffer, BUF_SIZE);
        // Read translated packet from slave
        int len = uart_read_bytes(UART_NUM1, slave_buffer, BUF_SIZE, (PACKET_READ_TICS * 2));
        // Check if the received packet is too short
        if (len > 2) {
            // Print received packet and check checksum
            esp_err_t status = print_packet_data("Received ", slave_buffer, len);
            if (status == ESP_OK) {
                good_count++;
                printf("Received: %d\r\n", good_count);
            } else {
                err_count++;
                printf("Errors: %d\r\n", err_count);
            }
        }
        else {
            printf("Incorrect answer from slave.\r\n");
            err_count++;
        }
    }
    // Free the buffer and delete driver at the end
    free(master_buffer);
    uart_driver_delete(UART_NUM1);
    TEST_ASSERT(err_count <= 1);
    printf("Test completed. Received packets = %d, errors = %d\r\n", (uint16_t)good_count, (uint16_t)err_count);
}