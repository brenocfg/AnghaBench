#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * rptr; } ;
struct TYPE_4__ {TYPE_2__* fifo_buf; } ;
typedef  TYPE_1__ FLACParseContext ;
typedef  TYPE_2__ AVFifoBuffer ;

/* Variables and functions */
 int FFMIN (int,int) ; 

__attribute__((used)) static uint8_t *flac_fifo_read(FLACParseContext *fpc, int offset, int *len)
{
    AVFifoBuffer *f   = fpc->fifo_buf;
    uint8_t *start    = f->rptr + offset;

    if (start >= f->end)
        start -= f->end - f->buffer;
    *len = FFMIN(*len, f->end - start);
    return start;
}