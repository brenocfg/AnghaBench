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
typedef  void uint8_t ;
struct TYPE_3__ {void* end; int buffer; void* rptr; } ;
typedef  TYPE_1__ AVFifoBuffer ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

int av_fifo_generic_peek(AVFifoBuffer *f, void *dest, int buf_size,
                         void (*func)(void *, void *, int))
{
// Read memory barrier needed for SMP here in theory
    uint8_t *rptr = f->rptr;

    do {
        int len = FFMIN(f->end - rptr, buf_size);
        if (func)
            func(dest, rptr, len);
        else {
            memcpy(dest, rptr, len);
            dest = (uint8_t *)dest + len;
        }
// memory barrier needed for SMP here in theory
        rptr += len;
        if (rptr >= f->end)
            rptr -= f->end - f->buffer;
        buf_size -= len;
    } while (buf_size > 0);

    return 0;
}