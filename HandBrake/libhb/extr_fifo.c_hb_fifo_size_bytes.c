#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_2__* first; } ;
typedef  TYPE_1__ hb_fifo_t ;
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ size; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

int hb_fifo_size_bytes( hb_fifo_t * f )
{
    int ret = 0;
    hb_buffer_t * link;

    hb_lock( f->lock );
    link = f->first;
    while ( link )
    {
        ret += link->size;
        link = link->next;
    }
    hb_unlock( f->lock );

    return ret;
}