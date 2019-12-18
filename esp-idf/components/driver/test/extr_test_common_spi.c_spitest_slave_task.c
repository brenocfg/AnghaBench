#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int trans_len; int /*<<< orphan*/ * rx_buffer; scalar_t__ tx_buffer; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ spi_slave_transaction_t ;
struct TYPE_7__ {int /*<<< orphan*/  spi; int /*<<< orphan*/  data_received; int /*<<< orphan*/  data_to_send; } ;
typedef  TYPE_2__ spi_slave_task_context_t ;
struct TYPE_8__ {scalar_t__ start; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ slave_txdata_t ;
typedef  int /*<<< orphan*/  RingbufHandle_t ;
typedef  int /*<<< orphan*/  QueueHandle_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SLAVE_TAG ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  spi_slave_transmit (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xQueueReceive (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xRingbufferSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void spitest_slave_task(void* arg)
{
    spi_slave_task_context_t* context = (spi_slave_task_context_t*) arg;
    QueueHandle_t queue = context->data_to_send;
    RingbufHandle_t ringbuf = context->data_received;
    uint8_t recvbuf[320+8];
    slave_txdata_t txdata;

    ESP_LOGI( SLAVE_TAG, "slave up" );
    //never quit, but blocked by the queue, waiting to be killed, when no more send from main task.
    while( 1 ) {
        BaseType_t ret = xQueueReceive( queue, &txdata, portMAX_DELAY );
        assert(ret);

        spi_slave_transaction_t t = {};
        t.length = txdata.len;
        t.tx_buffer = txdata.start;
        t.rx_buffer = recvbuf+8;
        //loop until trans_len != 0 to skip glitches
        do {
            TEST_ESP_OK( spi_slave_transmit( context->spi, &t, portMAX_DELAY ) );
        } while ( t.trans_len <= 2 );
        memcpy(recvbuf, &t.trans_len, sizeof(uint32_t));
        *(uint8_t**)(recvbuf+4) = (uint8_t*)txdata.start;
        ESP_LOGI( SLAVE_TAG, "received: %d", t.trans_len );
        xRingbufferSend( ringbuf, recvbuf, 8+(t.trans_len+7)/8, portMAX_DELAY );
    }
}