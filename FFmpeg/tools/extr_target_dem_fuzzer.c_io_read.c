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
struct TYPE_2__ {int pos; int fuzz; void* filesize; void* fuzz_size; } ;
typedef  TYPE_1__ IOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 void* FFMAX (void*,int) ; 
 void* FFMIN (int,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int io_read(void *opaque, uint8_t *buf, int buf_size)
{
    IOContext *c = opaque;
    int size = FFMIN(buf_size, c->fuzz_size);

    if (!c->fuzz_size) {
        c->filesize = FFMIN(c->pos, c->filesize);
        return AVERROR_EOF;
    }

    memcpy(buf, c->fuzz, size);
    c->fuzz      += size;
    c->fuzz_size -= size;
    c->pos       += size;
    c->filesize   = FFMAX(c->filesize, c->pos);

    return size;
}