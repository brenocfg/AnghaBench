#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {TYPE_2__* eth; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ emac_opencores_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* stack_input ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ ETH_MAX_PACKET_SIZE ; 
 scalar_t__ emac_opencores_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ulTaskNotifyTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_opencores_rx_task(void *arg)
{
    emac_opencores_t *emac = (emac_opencores_t *)arg;
    uint8_t *buffer = NULL;
    uint32_t length = 0;
    while (1) {
        if (ulTaskNotifyTake(pdFALSE, portMAX_DELAY)) {
            while(true) {
                buffer = (uint8_t *)malloc(ETH_MAX_PACKET_SIZE);
                length = ETH_MAX_PACKET_SIZE;
                if (emac_opencores_receive(&emac->parent, buffer, &length) == ESP_OK) {
                    // pass the buffer to the upper layer
                    if (length) {
                        emac->eth->stack_input(emac->eth, buffer, length);
                    } else {
                        free(buffer);
                    }
                } else {
                    free(buffer);
                    break;
                }
            }
        }
    }
    vTaskDelete(NULL);
}