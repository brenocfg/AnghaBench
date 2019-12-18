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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ rd; scalar_t__ wr; scalar_t__ size; } ;
typedef  TYPE_1__ esp_apptrace_rb_t ;

/* Variables and functions */

uint32_t esp_apptrace_rb_write_size_get(esp_apptrace_rb_t *rb)
{
    uint32_t size = 0;
    if (rb->rd <= rb->wr) {
        // |?R......W??|
        size = rb->size - rb->wr;
        if (size && rb->rd == 0) {
            size--;
        }
    } else {
        // |?W......R??|
        size = rb->rd - rb->wr - 1;
    }
    return size;
}