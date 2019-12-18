#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  paused; } ;
struct TYPE_8__ {TYPE_1__ working; } ;
struct TYPE_9__ {TYPE_2__ param; } ;
struct TYPE_11__ {int pause_date; scalar_t__ paused; int /*<<< orphan*/  pause_lock; int /*<<< orphan*/  pause_duration; TYPE_3__ state; TYPE_4__* current_job; } ;
typedef  TYPE_5__ hb_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  st_paused; } ;

/* Variables and functions */
 int hb_get_date () ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 

void hb_resume( hb_handle_t * h )
{
    if( h->paused )
    {
        if (h->pause_date != -1)
        {
            // Calculate paused time for current job sequence
            h->pause_duration    += hb_get_date() - h->pause_date;

            // Calculate paused time for current job pass
            // Required to calculate accurate ETA for pass
            h->current_job->st_paused += hb_get_date() - h->pause_date;
            h->pause_date              = -1;
            h->state.param.working.paused = h->pause_duration;
        }

        hb_unlock( h->pause_lock );
        h->paused = 0;
    }
}