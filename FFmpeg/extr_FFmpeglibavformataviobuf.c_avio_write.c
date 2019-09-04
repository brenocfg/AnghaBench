#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buf_end; scalar_t__ buf_ptr; int /*<<< orphan*/  update_checksum; scalar_t__ direct; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  avio_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  writeout (TYPE_1__*,unsigned char const*,int) ; 

void avio_write(AVIOContext *s, const unsigned char *buf, int size)
{
    if (s->direct && !s->update_checksum) {
        avio_flush(s);
        writeout(s, buf, size);
        return;
    }
    while (size > 0) {
        int len = FFMIN(s->buf_end - s->buf_ptr, size);
        memcpy(s->buf_ptr, buf, len);
        s->buf_ptr += len;

        if (s->buf_ptr >= s->buf_end)
            flush_buffer(s);

        buf += len;
        size -= len;
    }
}