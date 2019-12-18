#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* spi_device_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int spics_io_num; } ;
struct TYPE_9__ {TYPE_2__* host; int /*<<< orphan*/  semphr_polling; int /*<<< orphan*/  ret_queue; int /*<<< orphan*/  trans_queue; TYPE_1__ cfg; } ;
struct TYPE_8__ {int cur_cs; int prev_cs; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int NO_CS ; 
 int /*<<< orphan*/  SPI_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  spicommon_cs_free_io (int) ; 
 scalar_t__ uxQueueMessagesWaiting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 

esp_err_t spi_bus_remove_device(spi_device_handle_t handle)
{
    int x;
    SPI_CHECK(handle!=NULL, "invalid handle", ESP_ERR_INVALID_ARG);
    //These checks aren't exhaustive; another thread could sneak in a transaction inbetween. These are only here to
    //catch design errors and aren't meant to be triggered during normal operation.
    SPI_CHECK(uxQueueMessagesWaiting(handle->trans_queue)==0, "Have unfinished transactions", ESP_ERR_INVALID_STATE);
    SPI_CHECK(handle->host->cur_cs == NO_CS || atomic_load(&handle->host->device[handle->host->cur_cs])!=handle, "Have unfinished transactions", ESP_ERR_INVALID_STATE);
    SPI_CHECK(uxQueueMessagesWaiting(handle->ret_queue)==0, "Have unfinished transactions", ESP_ERR_INVALID_STATE);

    //return
    int spics_io_num = handle->cfg.spics_io_num;
    if (spics_io_num >= 0) spicommon_cs_free_io(spics_io_num);

    //Kill queues
    vQueueDelete(handle->trans_queue);
    vQueueDelete(handle->ret_queue);
    vSemaphoreDelete(handle->semphr_polling);
    //Remove device from list of csses and free memory
    for (x=0; x<NO_CS; x++) {
        if (atomic_load(&handle->host->device[x]) == handle){
            atomic_store(&handle->host->device[x], NULL);
            if (x == handle->host->prev_cs) handle->host->prev_cs = NO_CS;
        }
    }
    free(handle);
    return ESP_OK;
}