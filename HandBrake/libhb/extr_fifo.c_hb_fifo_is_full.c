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
struct TYPE_3__ {scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ hb_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

int hb_fifo_is_full( hb_fifo_t * f )
{
    int ret;

    hb_lock( f->lock );
    ret = ( f->size >= f->capacity );
    hb_unlock( f->lock );

    return ret;
}