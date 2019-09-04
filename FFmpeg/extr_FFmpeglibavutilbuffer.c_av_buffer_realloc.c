#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int size; TYPE_1__* buffer; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int flags; int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int BUFFER_FLAG_REALLOCATABLE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 TYPE_2__* av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_default_free ; 
 int /*<<< orphan*/  av_buffer_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buffer_replace (TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int av_buffer_realloc(AVBufferRef **pbuf, int size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;

    if (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(NULL, size);
        if (!data)
            return AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, NULL, 0);
        if (!buf) {
            av_freep(&data);
            return AVERROR(ENOMEM);
        }

        buf->buffer->flags |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        return 0;
    } else if (buf->size == size)
        return 0;

    if (!(buf->buffer->flags & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = NULL;

        av_buffer_realloc(&new, size);
        if (!new)
            return AVERROR(ENOMEM);

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        return 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    if (!tmp)
        return AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    return 0;
}