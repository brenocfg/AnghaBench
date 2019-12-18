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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond_full; int /*<<< orphan*/  cond_empty; } ;
typedef  TYPE_1__ hb_fifo_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_fifo_get (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void hb_fifo_flush( hb_fifo_t * f )
{
    hb_buffer_t * b;

    while( ( b = hb_fifo_get( f ) ) )
    {
        hb_buffer_close( &b );
    }
    hb_lock( f->lock );
    hb_cond_signal( f->cond_empty );
    hb_cond_signal( f->cond_full );
    hb_unlock( f->lock );

}