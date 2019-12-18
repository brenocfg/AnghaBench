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
struct TYPE_5__ {TYPE_1__* job; int /*<<< orphan*/ * die; } ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  int /*<<< orphan*/  hb_fifo_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_4__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 scalar_t__ hb_fifo_full_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_fifo_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_buf( hb_work_private_t *r, hb_fifo_t *fifo, hb_buffer_t *buf )
{
    while ( !*r->die && !r->job->done )
    {
        if ( hb_fifo_full_wait( fifo ) )
        {
            hb_fifo_push( fifo, buf );
            buf = NULL;
            break;
        }
    }
    if ( buf )
    {
        hb_buffer_close( &buf );
    }
}