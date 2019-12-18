#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* buffer; void* end; } ;
typedef  TYPE_1__ AVFifoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  av_free (void*) ; 
 TYPE_1__* av_mallocz (int) ; 

__attribute__((used)) static AVFifoBuffer *fifo_alloc_common(void *buffer, size_t size)
{
    AVFifoBuffer *f;
    if (!buffer)
        return NULL;
    f = av_mallocz(sizeof(AVFifoBuffer));
    if (!f) {
        av_free(buffer);
        return NULL;
    }
    f->buffer = buffer;
    f->end    = f->buffer + size;
    av_fifo_reset(f);
    return f;
}