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
struct TYPE_3__ {int /*<<< orphan*/  spi; int /*<<< orphan*/ * data_received; int /*<<< orphan*/ * data_to_send; } ;
typedef  TYPE_1__ spi_slave_task_context_t ;
typedef  int /*<<< orphan*/  slave_txdata_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RINGBUF_TYPE_NOSPLIT ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int /*<<< orphan*/ * xQueueCreate (int,int) ; 
 int /*<<< orphan*/ * xRingbufferCreate (int,int /*<<< orphan*/ ) ; 

esp_err_t init_slave_context(spi_slave_task_context_t *context)
{
    context->data_to_send = xQueueCreate( 16, sizeof( slave_txdata_t ));
    if ( context->data_to_send == NULL ) {
        return ESP_ERR_NO_MEM;
    }
    context->data_received = xRingbufferCreate( 1024, RINGBUF_TYPE_NOSPLIT );
    if ( context->data_received == NULL ) {
        return ESP_ERR_NO_MEM;
    }
    context->spi=TEST_SLAVE_HOST;
    return ESP_OK;
}