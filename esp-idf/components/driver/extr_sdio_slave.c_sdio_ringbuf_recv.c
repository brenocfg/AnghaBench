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
struct TYPE_4__ {int /*<<< orphan*/ * read_ptr; int /*<<< orphan*/ * write_ptr; int /*<<< orphan*/  item_size; int /*<<< orphan*/ * free_ptr; } ;
typedef  TYPE_1__ sdio_ringbuf_t ;
typedef  scalar_t__ ringbuf_get_all_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ RINGBUF_GET_ONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ringbuf_read_ptr ; 
 int /*<<< orphan*/ * sdio_ringbuf_offset_ptr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline esp_err_t sdio_ringbuf_recv(sdio_ringbuf_t* buf, uint8_t **start, uint8_t **end, ringbuf_get_all_t get_all, TickType_t wait)
{
    assert(buf->free_ptr == buf->read_ptr);   //must return before recv again
    assert(wait == 0);                          //only implement wait = 0 case now
    if (start == NULL && end == NULL) return ESP_ERR_INVALID_ARG; // must have a output
    if (buf->read_ptr == buf->write_ptr) return ESP_ERR_NOT_FOUND; // no data

    uint8_t *get_start = sdio_ringbuf_offset_ptr(buf, ringbuf_read_ptr, buf->item_size);

    if (get_all != RINGBUF_GET_ONE) {
        buf->read_ptr = buf->write_ptr;
    } else {
        buf->read_ptr = get_start;
    }

    if (start != NULL) *start = get_start;
    if (end != NULL)   *end = buf->read_ptr;
    return ESP_OK;
}