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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int wr; int rd; int size; int cur_size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ esp_apptrace_rb_t ;

/* Variables and functions */

uint8_t *esp_apptrace_rb_produce(esp_apptrace_rb_t *rb, uint32_t size)
{
    uint8_t *ptr = rb->data + rb->wr;
    // check for avalable space
    if (rb->rd <= rb->wr) {
        // |?R......W??|
        if (rb->wr + size >= rb->size) {
            if (rb->rd == 0) {
                return NULL; // cannot wrap wr
            }
            if (rb->wr + size == rb->size) {
                rb->wr = 0;
            } else {
                // check if we can wrap wr earlier to get space for requested size
                if (size > rb->rd - 1) {
                    return NULL; // cannot wrap wr
                }
                // shrink buffer a bit, full size will be restored at rd wrapping
                rb->cur_size = rb->wr;
                rb->wr = 0;
                ptr = rb->data;
                if (rb->rd == rb->cur_size) {
                    rb->rd = 0;
                    if (rb->cur_size < rb->size) {
                        rb->cur_size = rb->size;
                    }
                }
                rb->wr += size;
            }
        } else {
            rb->wr += size;
        }
    } else {
        // |?W......R??|
        if (size > rb->rd - rb->wr - 1) {
            return NULL;
        }
        rb->wr += size;
    }
    return ptr;
}