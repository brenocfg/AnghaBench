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
struct TYPE_6__ {int buf_end; int buf_ptr; int buffer_size; int eof_reached; int error; int pos; int bytes_read; int buffer; int /*<<< orphan*/  update_checksum; scalar_t__ direct; scalar_t__ write_flag; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFMIN (int,int) ; 
 scalar_t__ avio_feof (TYPE_1__*) ; 
 int /*<<< orphan*/  fill_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int,int) ; 
 int read_packet_wrapper (TYPE_1__*,unsigned char*,int) ; 

int avio_read(AVIOContext *s, unsigned char *buf, int size)
{
    int len, size1;

    size1 = size;
    while (size > 0) {
        len = FFMIN(s->buf_end - s->buf_ptr, size);
        if (len == 0 || s->write_flag) {
            if((s->direct || size > s->buffer_size) && !s->update_checksum) {
                // bypass the buffer and read data directly into buf
                len = read_packet_wrapper(s, buf, size);
                if (len == AVERROR_EOF) {
                    /* do not modify buffer if EOF reached so that a seek back can
                    be done without rereading data */
                    s->eof_reached = 1;
                    break;
                } else if (len < 0) {
                    s->eof_reached = 1;
                    s->error= len;
                    break;
                } else {
                    s->pos += len;
                    s->bytes_read += len;
                    size -= len;
                    buf += len;
                    // reset the buffer
                    s->buf_ptr = s->buffer;
                    s->buf_end = s->buffer/* + len*/;
                }
            } else {
                fill_buffer(s);
                len = s->buf_end - s->buf_ptr;
                if (len == 0)
                    break;
            }
        } else {
            memcpy(buf, s->buf_ptr, len);
            buf += len;
            s->buf_ptr += len;
            size -= len;
        }
    }
    if (size1 == size) {
        if (s->error)      return s->error;
        if (avio_feof(s))  return AVERROR_EOF;
    }
    return size1 - size;
}