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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int paused; int /*<<< orphan*/  state_lock; TYPE_1__ state; int /*<<< orphan*/  pause_date; int /*<<< orphan*/  pause_lock; } ;
typedef  TYPE_2__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_STATE_PAUSED ; 
 int /*<<< orphan*/  hb_get_date () ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void hb_pause( hb_handle_t * h )
{
    if( !h->paused )
    {
        hb_lock( h->pause_lock );
        h->paused = 1;

        h->pause_date = hb_get_date();

        hb_lock( h->state_lock );
        h->state.state = HB_STATE_PAUSED;
        hb_unlock( h->state_lock );
    }
}