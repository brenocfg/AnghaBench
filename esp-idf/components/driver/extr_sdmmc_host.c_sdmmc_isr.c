#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int sdmmc_status; int dma_status; } ;
typedef  TYPE_5__ sdmmc_event_t ;
struct TYPE_11__ {int sdio; } ;
struct TYPE_10__ {int val; int sdio; } ;
struct TYPE_9__ {int val; } ;
struct TYPE_8__ {int val; } ;
struct TYPE_13__ {TYPE_4__ intmask; TYPE_3__ mintsts; TYPE_2__ idsts; TYPE_1__ rintsts; } ;
typedef  int /*<<< orphan*/  QueueHandle_t ;

/* Variables and functions */
 TYPE_7__ SDMMC ; 
 int pdFALSE ; 
 int pdTRUE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  s_io_intr_event ; 
 int /*<<< orphan*/  xQueueSendFromISR (int /*<<< orphan*/ ,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  xSemaphoreGiveFromISR (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void sdmmc_isr(void* arg) {
    QueueHandle_t queue = (QueueHandle_t) arg;
    sdmmc_event_t event;
    int higher_priority_task_awoken = pdFALSE;

    uint32_t pending = SDMMC.mintsts.val & 0xFFFF;
    SDMMC.rintsts.val = pending;
    event.sdmmc_status = pending;

    uint32_t dma_pending = SDMMC.idsts.val;
    SDMMC.idsts.val = dma_pending;
    event.dma_status = dma_pending & 0x1f;

    if (pending != 0 || dma_pending != 0) {
        xQueueSendFromISR(queue, &event, &higher_priority_task_awoken);
    }

    uint32_t sdio_pending = SDMMC.mintsts.sdio;
    if (sdio_pending) {
        // disable the interrupt (no need to clear here, this is done in sdmmc_host_io_wait_int)
        SDMMC.intmask.sdio &= ~sdio_pending;
        xSemaphoreGiveFromISR(s_io_intr_event, &higher_priority_task_awoken);
    }

    if (higher_priority_task_awoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}