#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ capacity; int wait_full; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond_full; } ;
typedef  TYPE_1__ hb_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_TIMEOUT ; 
 int /*<<< orphan*/  hb_cond_timedwait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

int hb_fifo_full_wait( hb_fifo_t * f )
{
    int result;

    hb_lock( f->lock );
    if( f->size >= f->capacity )
    {
        f->wait_full = 1;
        hb_cond_timedwait( f->cond_full, f->lock, FIFO_TIMEOUT );
    }
    result = ( f->size < f->capacity );
    hb_unlock( f->lock );
    return result;
}