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
typedef  size_t uart_port_t ;
struct TYPE_6__ {size_t uart_num; int coll_det_flg; int queue_size; int rx_buffer_full_flg; int tx_waiting_fifo; int tx_buf_size; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/ * uart_select_notif_callback; int /*<<< orphan*/ * tx_ring_buf; void* rx_ring_buf; int /*<<< orphan*/ * rx_head_ptr; scalar_t__ rx_cur_remain; int /*<<< orphan*/ * rx_ptr; int /*<<< orphan*/ * xQueueUart; scalar_t__ rx_buffered_len; scalar_t__ tx_waiting_brk; scalar_t__ tx_brk_len; scalar_t__ tx_brk_flg; scalar_t__ tx_len_tot; int /*<<< orphan*/ * tx_head; int /*<<< orphan*/ * tx_ptr; void* rx_mux; void* tx_mux; void* tx_brk_sem; void* tx_done_sem; void* tx_fifo_sem; int /*<<< orphan*/  uart_mode; } ;
typedef  TYPE_1__ uart_obj_t ;
struct TYPE_7__ {int intr_enable_mask; int /*<<< orphan*/  txfifo_empty_intr_thresh; int /*<<< orphan*/  rx_timeout_thresh; int /*<<< orphan*/  rxfifo_full_thresh; } ;
typedef  TYPE_2__ uart_intr_config_t ;
typedef  int /*<<< orphan*/  uart_event_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/ * QueueHandle_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int ESP_INTR_FLAG_IRAM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RINGBUF_TYPE_BYTEBUF ; 
 int /*<<< orphan*/  RINGBUF_TYPE_NOSPLIT ; 
 int UART_BRK_DET_INT_ENA_M ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  UART_EMPTY_THRESH_DEFAULT ; 
 int UART_FIFO_LEN ; 
 int UART_FRM_ERR_INT_ENA_M ; 
 int /*<<< orphan*/  UART_FULL_THRESH_DEFAULT ; 
 int /*<<< orphan*/  UART_MODE_UART ; 
 size_t UART_NUM_MAX ; 
 int UART_PARITY_ERR_INT_ENA_M ; 
 int /*<<< orphan*/  UART_PATTERN_DET_QLEN_DEFAULT ; 
 int UART_RXFIFO_FULL_INT_ENA_M ; 
 int UART_RXFIFO_OVF_INT_ENA_M ; 
 int UART_RXFIFO_TOUT_INT_ENA_M ; 
 int /*<<< orphan*/  UART_TAG ; 
 int /*<<< orphan*/  UART_TOUT_THRESH_DEFAULT ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_1__** p_uart_obj ; 
 int /*<<< orphan*/  uart_driver_delete (size_t) ; 
 scalar_t__ uart_intr_config (size_t,TYPE_2__*) ; 
 scalar_t__ uart_isr_register (size_t,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_pattern_queue_reset (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_rx_intr_handler_default ; 
 int /*<<< orphan*/  uxQueueSpacesAvailable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xQueueCreate (int,int) ; 
 void* xRingbufferCreate (int,int /*<<< orphan*/ ) ; 
 void* xSemaphoreCreateBinary () ; 
 void* xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/  xSemaphoreGive (void*) ; 

esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size, int tx_buffer_size, int queue_size, QueueHandle_t *uart_queue, int intr_alloc_flags)
{
    esp_err_t r;
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_FAIL);
    UART_CHECK((rx_buffer_size > UART_FIFO_LEN), "uart rx buffer length error(>128)", ESP_FAIL);
    UART_CHECK((tx_buffer_size > UART_FIFO_LEN) || (tx_buffer_size == 0), "uart tx buffer length error(>128 or 0)", ESP_FAIL);
#if CONFIG_UART_ISR_IN_IRAM
    if ((intr_alloc_flags & ESP_INTR_FLAG_IRAM) == 0) {
        ESP_LOGI(UART_TAG, "ESP_INTR_FLAG_IRAM flag not set while CONFIG_UART_ISR_IN_IRAM is enabled, flag updated");
        intr_alloc_flags |= ESP_INTR_FLAG_IRAM;
    }
#else
    if ((intr_alloc_flags & ESP_INTR_FLAG_IRAM) != 0) {
        ESP_LOGW(UART_TAG, "ESP_INTR_FLAG_IRAM flag is set while CONFIG_UART_ISR_IN_IRAM is not enabled, flag updated");
        intr_alloc_flags &= ~ESP_INTR_FLAG_IRAM;
    }
#endif

    if (p_uart_obj[uart_num] == NULL) {
        p_uart_obj[uart_num] = (uart_obj_t *) calloc(1, sizeof(uart_obj_t));
        if (p_uart_obj[uart_num] == NULL) {
            ESP_LOGE(UART_TAG, "UART driver malloc error");
            return ESP_FAIL;
        }
        p_uart_obj[uart_num]->uart_num = uart_num;
        p_uart_obj[uart_num]->uart_mode = UART_MODE_UART;
        p_uart_obj[uart_num]->coll_det_flg = false;
        p_uart_obj[uart_num]->tx_fifo_sem = xSemaphoreCreateBinary();
        xSemaphoreGive(p_uart_obj[uart_num]->tx_fifo_sem);
        p_uart_obj[uart_num]->tx_done_sem = xSemaphoreCreateBinary();
        p_uart_obj[uart_num]->tx_brk_sem = xSemaphoreCreateBinary();
        p_uart_obj[uart_num]->tx_mux = xSemaphoreCreateMutex();
        p_uart_obj[uart_num]->rx_mux = xSemaphoreCreateMutex();
        p_uart_obj[uart_num]->queue_size = queue_size;
        p_uart_obj[uart_num]->tx_ptr = NULL;
        p_uart_obj[uart_num]->tx_head = NULL;
        p_uart_obj[uart_num]->tx_len_tot = 0;
        p_uart_obj[uart_num]->tx_brk_flg = 0;
        p_uart_obj[uart_num]->tx_brk_len = 0;
        p_uart_obj[uart_num]->tx_waiting_brk = 0;
        p_uart_obj[uart_num]->rx_buffered_len = 0;
        uart_pattern_queue_reset(uart_num, UART_PATTERN_DET_QLEN_DEFAULT);

        if (uart_queue) {
            p_uart_obj[uart_num]->xQueueUart = xQueueCreate(queue_size, sizeof(uart_event_t));
            *uart_queue = p_uart_obj[uart_num]->xQueueUart;
            ESP_LOGI(UART_TAG, "queue free spaces: %d", uxQueueSpacesAvailable(p_uart_obj[uart_num]->xQueueUart));
        } else {
            p_uart_obj[uart_num]->xQueueUart = NULL;
        }
        p_uart_obj[uart_num]->rx_buffer_full_flg = false;
        p_uart_obj[uart_num]->tx_waiting_fifo = false;
        p_uart_obj[uart_num]->rx_ptr = NULL;
        p_uart_obj[uart_num]->rx_cur_remain = 0;
        p_uart_obj[uart_num]->rx_head_ptr = NULL;
        p_uart_obj[uart_num]->rx_ring_buf = xRingbufferCreate(rx_buffer_size, RINGBUF_TYPE_BYTEBUF);
        if (tx_buffer_size > 0) {
            p_uart_obj[uart_num]->tx_ring_buf = xRingbufferCreate(tx_buffer_size, RINGBUF_TYPE_NOSPLIT);
            p_uart_obj[uart_num]->tx_buf_size = tx_buffer_size;
        } else {
            p_uart_obj[uart_num]->tx_ring_buf = NULL;
            p_uart_obj[uart_num]->tx_buf_size = 0;
        }
        p_uart_obj[uart_num]->uart_select_notif_callback = NULL;
    } else {
        ESP_LOGE(UART_TAG, "UART driver already installed");
        return ESP_FAIL;
    }

    r = uart_isr_register(uart_num, uart_rx_intr_handler_default, p_uart_obj[uart_num], intr_alloc_flags, &p_uart_obj[uart_num]->intr_handle);
    if (r != ESP_OK) {
        goto err;
    }
    uart_intr_config_t uart_intr = {
        .intr_enable_mask = UART_RXFIFO_FULL_INT_ENA_M
        | UART_RXFIFO_TOUT_INT_ENA_M
        | UART_FRM_ERR_INT_ENA_M
        | UART_RXFIFO_OVF_INT_ENA_M
        | UART_BRK_DET_INT_ENA_M
        | UART_PARITY_ERR_INT_ENA_M,
        .rxfifo_full_thresh = UART_FULL_THRESH_DEFAULT,
        .rx_timeout_thresh = UART_TOUT_THRESH_DEFAULT,
        .txfifo_empty_intr_thresh = UART_EMPTY_THRESH_DEFAULT
    };
    r = uart_intr_config(uart_num, &uart_intr);
    if (r != ESP_OK) {
        goto err;
    }
    return r;

err:
    uart_driver_delete(uart_num);
    return r;
}