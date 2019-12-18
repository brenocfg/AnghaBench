#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {void* limit; void* size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  void* int32_t ;

/* Variables and functions */

void mz_stream_mem_set_buffer(void *stream, void *buf, int32_t size)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    mem->buffer = (uint8_t *)buf;
    mem->size = size;
    mem->limit = size;
}