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
struct TYPE_4__ {int item_size; int read_ptr; int size; int free_ptr; int /*<<< orphan*/  remain_cnt; } ;
typedef  TYPE_1__ sdio_ringbuf_t ;
typedef  scalar_t__ portBASE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  ringbuf_free_ptr ; 
 int /*<<< orphan*/ * sdio_ringbuf_offset_ptr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xSemaphoreGiveFromISR (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline void sdio_ringbuf_return_from_isr(sdio_ringbuf_t* buf, uint8_t *ptr, portBASE_TYPE *yield)
{
    assert(sdio_ringbuf_offset_ptr(buf, ringbuf_free_ptr, buf->item_size) == ptr);
    int size = (buf->read_ptr + buf->size - buf->free_ptr)%buf->size;
    int count = size/buf->item_size;
    assert(count*buf->item_size==size);
    buf->free_ptr = buf->read_ptr;
    for(int i = 0; i < count; i++) {
        portBASE_TYPE ret = xSemaphoreGiveFromISR(buf->remain_cnt, yield);
        assert(ret == pdTRUE);
    }
}