#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdmmc_event_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_9__ {scalar_t__ busy_clr_int_en; } ;
struct TYPE_8__ {int int_enable; } ;
struct TYPE_7__ {int val; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_10__ {TYPE_4__ cardthrctl; TYPE_3__ ctrl; TYPE_2__ intmask; TYPE_1__ rintsts; int /*<<< orphan*/  hcon; int /*<<< orphan*/  verid; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ETS_SDIO_HOST_INTR_SOURCE ; 
 int /*<<< orphan*/  PERIPH_SDMMC_MODULE ; 
 TYPE_5__ SDMMC ; 
 int /*<<< orphan*/  SDMMC_EVENT_QUEUE_LENGTH ; 
 int SDMMC_INTMASK_CD ; 
 int SDMMC_INTMASK_CMD_DONE ; 
 int SDMMC_INTMASK_DATA_OVER ; 
 int SDMMC_INTMASK_DCRC ; 
 int SDMMC_INTMASK_DTO ; 
 int SDMMC_INTMASK_EBE ; 
 int SDMMC_INTMASK_HLE ; 
 int SDMMC_INTMASK_HTO ; 
 int SDMMC_INTMASK_RCRC ; 
 int SDMMC_INTMASK_RESP_ERR ; 
 int SDMMC_INTMASK_RTO ; 
 int SDMMC_INTMASK_SBE ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_module_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_event_queue ; 
 int /*<<< orphan*/ * s_intr_handle ; 
 int /*<<< orphan*/ * s_io_intr_event ; 
 int /*<<< orphan*/  sdmmc_host_dma_init () ; 
 int /*<<< orphan*/  sdmmc_host_reset () ; 
 int /*<<< orphan*/  sdmmc_host_set_clk_div (int) ; 
 scalar_t__ sdmmc_host_transaction_handler_init () ; 
 int /*<<< orphan*/  sdmmc_isr ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xSemaphoreCreateBinary () ; 

esp_err_t sdmmc_host_init(void)
{
    if (s_intr_handle) {
        return ESP_ERR_INVALID_STATE;
    }

    periph_module_reset(PERIPH_SDMMC_MODULE);
    periph_module_enable(PERIPH_SDMMC_MODULE);

    // Enable clock to peripheral. Use smallest divider first.
    sdmmc_host_set_clk_div(2);

    // Reset
    sdmmc_host_reset();
    ESP_LOGD(TAG, "peripheral version %x, hardware config %08x", SDMMC.verid, SDMMC.hcon);

    // Clear interrupt status and set interrupt mask to known state
    SDMMC.rintsts.val = 0xffffffff;
    SDMMC.intmask.val = 0;
    SDMMC.ctrl.int_enable = 0;

    // Allocate event queue
    s_event_queue = xQueueCreate(SDMMC_EVENT_QUEUE_LENGTH, sizeof(sdmmc_event_t));
    if (!s_event_queue) {
        return ESP_ERR_NO_MEM;
    }
    s_io_intr_event = xSemaphoreCreateBinary();
    if (!s_io_intr_event) {
        vQueueDelete(s_event_queue);
        s_event_queue = NULL;
        return ESP_ERR_NO_MEM;
    }
    // Attach interrupt handler
    esp_err_t ret = esp_intr_alloc(ETS_SDIO_HOST_INTR_SOURCE, 0, &sdmmc_isr, s_event_queue, &s_intr_handle);
    if (ret != ESP_OK) {
        vQueueDelete(s_event_queue);
        s_event_queue = NULL;
        vSemaphoreDelete(s_io_intr_event);
        s_io_intr_event = NULL;
        return ret;
    }
    // Enable interrupts
    SDMMC.intmask.val =
            SDMMC_INTMASK_CD |
            SDMMC_INTMASK_CMD_DONE |
            SDMMC_INTMASK_DATA_OVER |
            SDMMC_INTMASK_RCRC | SDMMC_INTMASK_DCRC |
            SDMMC_INTMASK_RTO | SDMMC_INTMASK_DTO | SDMMC_INTMASK_HTO |
            SDMMC_INTMASK_SBE | SDMMC_INTMASK_EBE |
            SDMMC_INTMASK_RESP_ERR | SDMMC_INTMASK_HLE; //sdio is enabled only when use.
    SDMMC.ctrl.int_enable = 1;

    // Disable generation of Busy Clear Interrupt
    SDMMC.cardthrctl.busy_clr_int_en = 0;

    // Enable DMA
    sdmmc_host_dma_init();

    // Initialize transaction handler
    ret = sdmmc_host_transaction_handler_init();
    if (ret != ESP_OK) {
        vQueueDelete(s_event_queue);
        s_event_queue = NULL;
        vSemaphoreDelete(s_io_intr_event);
        s_io_intr_event = NULL;
        esp_intr_free(s_intr_handle);
        s_intr_handle = NULL;
        return ret;
    }

    return ESP_OK;
}