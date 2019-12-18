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
struct TYPE_4__ {scalar_t__ read_ptr; scalar_t__ write_ptr; int /*<<< orphan*/  item_size; } ;
typedef  TYPE_1__ sdio_ringbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ringbuf_read_ptr ; 
 int /*<<< orphan*/ * sdio_ringbuf_offset_ptr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t* sdio_ringbuf_peek_front(sdio_ringbuf_t* buf)
{
    if (buf->read_ptr != buf->write_ptr) {
        return sdio_ringbuf_offset_ptr(buf, ringbuf_read_ptr, buf->item_size);
    } else {
        return NULL;
    }
}