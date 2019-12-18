#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* freq_list; int const freq_limit; int test_size; scalar_t__ dup; int const master_limit; int /*<<< orphan*/  pset_name; } ;
typedef  TYPE_2__ spitest_param_set_t ;
struct TYPE_8__ {int /*<<< orphan*/  data_received; } ;
struct TYPE_10__ {TYPE_1__ slave_context; int /*<<< orphan*/ * master_trans; } ;
typedef  TYPE_3__ spitest_context_t ;
typedef  int /*<<< orphan*/  spi_transaction_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
typedef  int /*<<< orphan*/  slave_rxdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ HALF_DUPLEX_MISO ; 
 scalar_t__ HALF_DUPLEX_MOSI ; 
 int /*<<< orphan*/  MASTER_TAG ; 
 int /*<<< orphan*/  SLAVE_TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int get_trans_len (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_test_start (int /*<<< orphan*/ *,int const,TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  master_free_device_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  spi_device_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spi_slave_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitest_check_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int) ; 
 int /*<<< orphan*/  spitest_init_transactions (TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  spitest_master_print_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spitest_slave_print_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/ * xRingbufferReceive (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void local_test_loop(const void* arg1, void* arg2)
{
    const spitest_param_set_t *pset = arg1;
    spitest_context_t *context = arg2;
    spi_device_handle_t spi;
    spitest_init_transactions(pset, context);
    const int *timing_speed_array = pset->freq_list;

    ESP_LOGI(MASTER_TAG, "****************** %s ***************", pset->pset_name);
    for (int i = 0; ; i++) {
        const int freq = timing_speed_array[i];
        if (freq==0) break;
        if (pset->freq_limit && freq > pset->freq_limit) break;

        ESP_LOGI(MASTER_TAG, "======> %dk", freq / 1000);
        local_test_start(&spi, freq, pset, context);

        for (int k = 0; k < pset->test_size; k++) {
            //wait for both master and slave end
            ESP_LOGI(MASTER_TAG, "=> test%d", k);
            //send master tx data
            vTaskDelay(9);

            spi_transaction_t *t = &context->master_trans[k];
            TEST_ESP_OK(spi_device_transmit(spi, t));
            int len = get_trans_len(pset->dup, t);
            spitest_master_print_data(t, len);

            size_t rcv_len;
            slave_rxdata_t *rcv_data = xRingbufferReceive(context->slave_context.data_received, &rcv_len, portMAX_DELAY);
            spitest_slave_print_data(rcv_data, true);

            //check result
            bool check_master_data = (pset->dup!=HALF_DUPLEX_MOSI &&
                    (pset->master_limit==0 || freq <= pset->master_limit));
            bool check_slave_data = (pset->dup!=HALF_DUPLEX_MISO);
            const bool check_len = true;
            if (!check_master_data) ESP_LOGI(MASTER_TAG, "skip master data check");
            if (!check_slave_data) ESP_LOGI(SLAVE_TAG, "skip slave data check");

            TEST_ESP_OK(spitest_check_data(len, t, rcv_data, check_master_data, check_len, check_slave_data));
            //clean
            vRingbufferReturnItem(context->slave_context.data_received, rcv_data);
        }
        master_free_device_bus(spi);
        TEST_ASSERT(spi_slave_free(TEST_SLAVE_HOST) == ESP_OK);
    }
}