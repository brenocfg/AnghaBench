#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int size; void (* free ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  refcount; void* opaque; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * data; TYPE_2__* buffer; } ;
typedef  TYPE_1__ AVBufferRef ;
typedef  TYPE_2__ AVBuffer ;

/* Variables and functions */
 int AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 void av_buffer_default_free (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 

AVBufferRef *av_buffer_create(uint8_t *data, int size,
                              void (*free)(void *opaque, uint8_t *data),
                              void *opaque, int flags)
{
    AVBufferRef *ref = NULL;
    AVBuffer    *buf = NULL;

    buf = av_mallocz(sizeof(*buf));
    if (!buf)
        return NULL;

    buf->data     = data;
    buf->size     = size;
    buf->free     = free ? free : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    if (flags & AV_BUFFER_FLAG_READONLY)
        buf->flags |= BUFFER_FLAG_READONLY;

    ref = av_mallocz(sizeof(*ref));
    if (!ref) {
        av_freep(&buf);
        return NULL;
    }

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    return ref;
}