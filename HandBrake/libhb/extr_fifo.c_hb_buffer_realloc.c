#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int buffer_size; } ;
typedef  TYPE_1__ hb_fifo_t ;
struct TYPE_7__ {int alloc; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ hb_buffer_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 TYPE_5__ buffers ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* size_to_pool (int) ; 

void hb_buffer_realloc( hb_buffer_t * b, int size )
{
    if ( size > b->alloc || b->data == NULL )
    {
        uint8_t   * tmp;
        uint32_t    orig = b->data != NULL ? b->alloc : 0;
        hb_fifo_t * buffer_pool = size_to_pool(size);

        if (buffer_pool != NULL)
        {
            size = buffer_pool->buffer_size;
        }
        tmp = av_malloc(size);
        if (tmp == NULL)
        {
            return;
        }
        if (b->data != NULL)
        {
            memcpy(tmp, b->data, b->alloc);
            av_free(b->data);
        }
        b->data  = tmp;
        b->alloc = size;

        hb_lock(buffers.lock);
        buffers.allocated += size - orig;
        hb_unlock(buffers.lock);
    }
}