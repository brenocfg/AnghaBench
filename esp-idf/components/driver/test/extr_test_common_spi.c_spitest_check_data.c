#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  tx_buffer; int /*<<< orphan*/  rx_buffer; } ;
typedef  TYPE_1__ spi_transaction_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  tx_start; } ;
typedef  TYPE_2__ slave_rxdata_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX8_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

esp_err_t spitest_check_data(int len, spi_transaction_t *master_t, slave_rxdata_t *slave_t, bool check_master_data, bool check_slave_len, bool check_slave_data)
{
    //currently the rcv_len can be in range of [t->length-1, t->length+3]
    if (check_slave_len) {
        uint32_t rcv_len = slave_t->len;
        TEST_ASSERT(rcv_len >= len - 1 && rcv_len <= len + 4);
    }

    if (check_master_data) {
        TEST_ASSERT_EQUAL_HEX8_ARRAY(slave_t->tx_start, master_t->rx_buffer, (len + 7) / 8);
    }

    if (check_slave_data) {
        TEST_ASSERT_EQUAL_HEX8_ARRAY(master_t->tx_buffer, slave_t->data, (len + 7) / 8);
    }
    return ESP_OK;
}