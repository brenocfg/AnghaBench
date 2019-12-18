#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int item_size; int size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * free_ptr; int /*<<< orphan*/ * read_ptr; int /*<<< orphan*/ * write_ptr; int /*<<< orphan*/ * remain_cnt; } ;
typedef  TYPE_1__ sdio_ringbuf_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SDIO_SLAVE_LOGE (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sdio_ringbuf_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/ * xSemaphoreCreateCounting (int,int) ; 

__attribute__((used)) static esp_err_t sdio_ringbuf_init(sdio_ringbuf_t* buf, int item_size, int item_cnt)
{
    if (buf->data != NULL) {
        SDIO_SLAVE_LOGE("sdio_ringbuf_init: already initialized");
        return ESP_ERR_INVALID_STATE;
    }
    buf->item_size = item_size;
    //one item is not used.
    buf->size = item_size * (item_cnt+1);
    //apply for resources
    buf->data = (uint8_t*)malloc(buf->size);
    if (buf->data == NULL) goto no_mem;
    buf->remain_cnt = xSemaphoreCreateCounting(item_cnt, item_cnt);
    if (buf->remain_cnt == NULL) goto no_mem;
    //initialize pointers
    buf->write_ptr = buf->data;
    buf->read_ptr = buf->data;
    buf->free_ptr = buf->data;
    return ESP_OK;
no_mem:
    sdio_ringbuf_deinit(buf);
    return ESP_ERR_NO_MEM;
}