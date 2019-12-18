#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int buffer_size; int orig_buffer_size; int /*<<< orphan*/ * buf_ptr; int /*<<< orphan*/ * buffer; scalar_t__ write_flag; int /*<<< orphan*/ * buf_end; int /*<<< orphan*/ * buf_ptr_max; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int ffio_set_buf_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ffio_realloc_buf(AVIOContext *s, int buf_size)
{
    uint8_t *buffer;
    int data_size;

    if (!s->buffer_size)
        return ffio_set_buf_size(s, buf_size);

    if (buf_size <= s->buffer_size)
        return 0;

    buffer = av_malloc(buf_size);
    if (!buffer)
        return AVERROR(ENOMEM);

    data_size = s->write_flag ? (s->buf_ptr - s->buffer) : (s->buf_end - s->buf_ptr);
    if (data_size > 0)
        memcpy(buffer, s->write_flag ? s->buffer : s->buf_ptr, data_size);
    av_free(s->buffer);
    s->buffer = buffer;
    s->orig_buffer_size = buf_size;
    s->buffer_size = buf_size;
    s->buf_ptr = s->write_flag ? (s->buffer + data_size) : s->buffer;
    if (s->write_flag)
        s->buf_ptr_max = s->buffer + data_size;

    s->buf_end = s->write_flag ? (s->buffer + s->buffer_size) : (s->buf_ptr + data_size);

    return 0;
}