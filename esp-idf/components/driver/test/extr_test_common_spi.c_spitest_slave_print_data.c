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
struct TYPE_3__ {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  tx_start; } ;
typedef  TYPE_1__ slave_rxdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEX (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SLAVE_TAG ; 

void spitest_slave_print_data(slave_rxdata_t *t, bool print_rxdata)
{
    int rcv_len = (t->len+7)/8;
    ESP_LOGI(SLAVE_TAG, "trans_len: %d", t->len);
    ESP_LOG_BUFFER_HEX("slave tx", t->tx_start, rcv_len);
    if (print_rxdata) ESP_LOG_BUFFER_HEX("slave rx", t->data, rcv_len);
}