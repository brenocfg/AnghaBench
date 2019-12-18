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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/  lock; TYPE_2__* first; TYPE_2__* last; int /*<<< orphan*/ * cond_alert_full; } ;
typedef  TYPE_1__ hb_fifo_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void hb_fifo_push_head( hb_fifo_t * f, hb_buffer_t * b )
{
    hb_buffer_t * tmp;
    uint32_t      size = 0;

    if( !b )
    {
        return;
    }

    hb_lock( f->lock );
    if (f->size >= f->capacity &&
        f->cond_alert_full != NULL)
    {
        hb_cond_broadcast( f->cond_alert_full );
    }

    /*
     * If there are a chain of buffers prepend the lot
     */
    tmp = b;
    while( tmp->next )
    {
        tmp = tmp->next;
        size += 1;
    }

    if( f->size > 0 )
    {
        tmp->next = f->first;
    }
    else
    {
        f->last = tmp;
    }

    f->first = b;
    f->size += ( size + 1 );

    hb_unlock( f->lock );
}