#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int finished; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ task_context_t ;
struct TYPE_5__ {int length; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ spi_transaction_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SPI_TRANS_USE_TXDATA ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  spi_device_acquire_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_device_polling_transmit (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  spi_device_release_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

void spi_task1(void* arg)
{
    //task1 send 50 polling transactions, acquire the bus and send another 50
    int count=0;
    spi_transaction_t t = {
        .flags = SPI_TRANS_USE_TXDATA,
        .tx_data = { 0x80, 0x12, 0x34, 0x56 },
        .length = 4*8,
    };
    spi_device_handle_t handle = ((task_context_t*)arg)->handle;
    for( int j = 0; j < 50; j ++ ) {
        TEST_ESP_OK(spi_device_polling_transmit( handle, &t ));
        ESP_LOGI( TAG, "task1:%d", count++ );
    }
    TEST_ESP_OK(spi_device_acquire_bus( handle, portMAX_DELAY ));
    for( int j = 0; j < 50; j ++ ) {
        TEST_ESP_OK(spi_device_polling_transmit( handle, &t ));
        ESP_LOGI( TAG, "task1:%d", count++ );
    }
    spi_device_release_bus(handle);
    ESP_LOGI(TAG, "task1 terminates");
    ((task_context_t*)arg)->finished = true;
    vTaskDelete(NULL);
}