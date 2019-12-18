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
struct TYPE_9__ {int pset_name; int* freq_list; int const freq_limit; int test_size; scalar_t__ dup; } ;
typedef  TYPE_2__ spitest_param_set_t ;
struct TYPE_8__ {int /*<<< orphan*/  data_received; int /*<<< orphan*/  data_to_send; } ;
struct TYPE_10__ {TYPE_1__ slave_context; int /*<<< orphan*/ * master_trans; int /*<<< orphan*/ * slave_trans; } ;
typedef  TYPE_3__ spitest_context_t ;
typedef  int /*<<< orphan*/  spi_transaction_t ;
typedef  int /*<<< orphan*/  slave_rxdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int const) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  FULL_DUPLEX ; 
 scalar_t__ HALF_DUPLEX_MISO ; 
 int /*<<< orphan*/  MASTER_TAG ; 
 int /*<<< orphan*/  SLAVE_TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int get_trans_len (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ spi_slave_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitest_check_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,int) ; 
 int /*<<< orphan*/  spitest_init_transactions (TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  spitest_master_print_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitest_slave_print_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timing_slave_start (int const,TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  unity_send_signal (char*) ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  xQueueSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xRingbufferReceive (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_slave_loop(const void *arg1, void* arg2)
{
    const spitest_param_set_t *pset = (spitest_param_set_t*)arg1;
    spitest_context_t* context = (spitest_context_t*)arg2;
    ESP_LOGI(SLAVE_TAG, "****************** %s ***************", pset->pset_name);
    spitest_init_transactions(pset, context);

    const int *timing_speed_array = pset->freq_list;
    for (int i=0; ; i++ ) {
        const int freq = timing_speed_array[i];
        if (freq==0) break;
        if (pset->freq_limit != 0 && freq > pset->freq_limit) break;

        ESP_LOGI(MASTER_TAG, "==============> %dk", timing_speed_array[i]/1000);
        //Initialize SPI slave interface
        timing_slave_start(freq, pset, context);

        //prepare slave tx data
        for (int i = 0; i < pset->test_size; i ++) {
            xQueueSend( context->slave_context.data_to_send, &context->slave_trans[i], portMAX_DELAY );
            //memcpy(context->master_trans[i].rx_buffer, context->slave_trans[i].start, (context->master_trans[i].length+7)/8);
        }

        vTaskDelay(50/portTICK_PERIOD_MS);
        unity_send_signal("slave ready");

        for( int i= 0; i < pset->test_size; i ++ ) {
            //wait for both master and slave end
            ESP_LOGI( MASTER_TAG, "===== test%d =====", i );
            //send master tx data
            vTaskDelay(20);

            spi_transaction_t *t = &context->master_trans[i];
            int len = get_trans_len(pset->dup, t);
            spitest_master_print_data(t, FULL_DUPLEX);

            size_t rcv_len;
            slave_rxdata_t *rcv_data = xRingbufferReceive( context->slave_context.data_received, &rcv_len, portMAX_DELAY );
            spitest_slave_print_data(rcv_data, true);

            //check result
            const bool check_master_data = false;
            bool check_slave_data = (pset->dup!=HALF_DUPLEX_MISO);
            const bool check_len = true;
            TEST_ESP_OK(spitest_check_data(len, t, rcv_data, check_master_data, check_len, check_slave_data));
            //clean
            vRingbufferReturnItem( context->slave_context.data_received, rcv_data );
        }
        TEST_ASSERT(spi_slave_free(TEST_SLAVE_HOST) == ESP_OK);
    }
}