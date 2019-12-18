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
struct TYPE_6__ {int pos; int buf_end; int buf_ptr; int buffer; int error; scalar_t__ write_flag; scalar_t__ read_packet; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ avio_feof (TYPE_1__*) ; 
 int /*<<< orphan*/  fill_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int,int) ; 
 int read_packet_wrapper (TYPE_1__*,unsigned char*,int) ; 

int avio_read_partial(AVIOContext *s, unsigned char *buf, int size)
{
    int len;

    if (size < 0)
        return -1;

    if (s->read_packet && s->write_flag) {
        len = read_packet_wrapper(s, buf, size);
        if (len > 0)
            s->pos += len;
        return len;
    }

    len = s->buf_end - s->buf_ptr;
    if (len == 0) {
        /* Reset the buf_end pointer to the start of the buffer, to make sure
         * the fill_buffer call tries to read as much data as fits into the
         * full buffer, instead of just what space is left after buf_end.
         * This avoids returning partial packets at the end of the buffer,
         * for packet based inputs.
         */
        s->buf_end = s->buf_ptr = s->buffer;
        fill_buffer(s);
        len = s->buf_end - s->buf_ptr;
    }
    if (len > size)
        len = size;
    memcpy(buf, s->buf_ptr, len);
    s->buf_ptr += len;
    if (!len) {
        if (s->error)      return s->error;
        if (avio_feof(s))  return AVERROR_EOF;
    }
    return len;
}