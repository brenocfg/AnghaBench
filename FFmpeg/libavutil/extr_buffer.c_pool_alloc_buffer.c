#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  size; TYPE_3__* (* alloc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  opaque; TYPE_3__* (* alloc2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_1__* buffer; } ;
struct TYPE_12__ {TYPE_4__* pool; int /*<<< orphan*/  free; struct TYPE_12__* opaque; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  free; TYPE_2__* opaque; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ BufferPoolEntry ;
typedef  TYPE_3__ AVBufferRef ;
typedef  TYPE_4__ AVBufferPool ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 
 TYPE_2__* av_mallocz (int) ; 
 int /*<<< orphan*/  pool_release_buffer ; 
 TYPE_3__* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    if (!ret)
        return NULL;

    buf = av_mallocz(sizeof(*buf));
    if (!buf) {
        av_buffer_unref(&ret);
        return NULL;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->free   = ret->buffer->free;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->free   = pool_release_buffer;

    return ret;
}