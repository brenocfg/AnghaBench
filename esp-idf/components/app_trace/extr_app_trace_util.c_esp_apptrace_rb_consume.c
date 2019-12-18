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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int rd; scalar_t__ wr; scalar_t__ cur_size; scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ esp_apptrace_rb_t ;

/* Variables and functions */

uint8_t *esp_apptrace_rb_consume(esp_apptrace_rb_t *rb, uint32_t size)
{
    uint8_t *ptr = rb->data + rb->rd;
    if (rb->rd <= rb->wr) {
        // |?R......W??|
        if (rb->rd + size > rb->wr) {
            return NULL;
        }
        rb->rd += size;
    } else {
        // |?W......R??|
        if (rb->rd + size > rb->cur_size) {
            return NULL;
        } else if (rb->rd + size == rb->cur_size) {
            // restore full size usage
            if (rb->cur_size < rb->size) {
                rb->cur_size = rb->size;
            }
            rb->rd = 0;
        } else {
            rb->rd += size;
        }
    }
    return ptr;
}