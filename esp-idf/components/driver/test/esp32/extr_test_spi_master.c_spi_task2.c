#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int finished; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ task_context_t ;
struct TYPE_7__ {int length; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ spi_transaction_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SPI_TRANS_USE_TXDATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  spi_device_acquire_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_device_get_trans_result (int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_device_polling_transmit (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  spi_device_queue_trans (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_device_release_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

void spi_task2(void* arg)
{
    int count=0;
    //task2 acquire the bus, send 50 polling transactions and then 50 non-polling
    spi_transaction_t t = {
        .flags = SPI_TRANS_USE_TXDATA,
        .tx_data = { 0x80, 0x12, 0x34, 0x56 },
        .length = 4*8,
    };
    spi_transaction_t *ret_t;
    spi_device_handle_t handle = ((task_context_t*)arg)->handle;
    TEST_ESP_OK(spi_device_acquire_bus( handle, portMAX_DELAY ));

    for (int i = 0; i < 50; i ++) {
        TEST_ESP_OK(spi_device_polling_transmit(handle, &t));
        ESP_LOGI( TAG, "task2: %d", count++ );
    }

    for( int j = 0; j < 50; j ++ ) {
        TEST_ESP_OK(spi_device_queue_trans( handle, &t, portMAX_DELAY ));
    }
    for( int j = 0; j < 50; j ++ ) {
        TEST_ESP_OK(spi_device_get_trans_result(handle, &ret_t, portMAX_DELAY));
        assert(ret_t == &t);
        ESP_LOGI( TAG, "task2: %d", count++ );
    }
    spi_device_release_bus(handle);
    vTaskDelay(1);
    ESP_LOGI(TAG, "task2 terminates");
    ((task_context_t*)arg)->finished = true;
    vTaskDelete(NULL);
}