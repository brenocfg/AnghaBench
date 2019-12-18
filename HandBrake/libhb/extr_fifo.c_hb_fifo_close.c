#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cond_full; int /*<<< orphan*/  cond_empty; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ hb_fifo_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_list_rem (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_cond_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_fifo_get (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_fifo_size (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_lock_close (int /*<<< orphan*/ *) ; 

void hb_fifo_close( hb_fifo_t ** _f )
{
    hb_fifo_t   * f = *_f;
    hb_buffer_t * b;

    if ( f == NULL )
        return;

    hb_deep_log( 2, "fifo_close: trashing %d buffer(s)", hb_fifo_size( f ) );
    while( ( b = hb_fifo_get( f ) ) )
    {
        hb_buffer_close( &b );
    }

    hb_lock_close( &f->lock );
    hb_cond_close( &f->cond_empty );
    hb_cond_close( &f->cond_full );

#if defined(HB_FIFO_DEBUG)
    // Remove the fifo from the global fifo list
    fifo_list_rem( f );
#endif

    free( f );

    *_f = NULL;
}