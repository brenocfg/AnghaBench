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
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ hb_state_t ;

/* Variables and functions */
 scalar_t__ HB_STATE_PAUSED ; 
 int /*<<< orphan*/  ghb_pause_queue () ; 
 int /*<<< orphan*/  ghb_resume_queue () ; 
 int /*<<< orphan*/  h_queue ; 
 int /*<<< orphan*/  hb_get_state2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
ghb_pause_resume_queue()
{
    hb_state_t s;
    hb_get_state2( h_queue, &s );

    if( s.state == HB_STATE_PAUSED )
    {
        ghb_resume_queue();
    }
    else
    {
        ghb_pause_queue();
    }
}