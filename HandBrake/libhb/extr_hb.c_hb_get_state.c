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
typedef  int /*<<< orphan*/  hb_state_t ;
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  state_lock; TYPE_2__ state; } ;
typedef  TYPE_1__ hb_handle_t ;

/* Variables and functions */
 scalar_t__ HB_STATE_IDLE ; 
 scalar_t__ HB_STATE_SCANDONE ; 
 scalar_t__ HB_STATE_WORKDONE ; 
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

void hb_get_state( hb_handle_t * h, hb_state_t * s )
{
    hb_lock( h->state_lock );

    memcpy( s, &h->state, sizeof( hb_state_t ) );
    if ( h->state.state == HB_STATE_SCANDONE || h->state.state == HB_STATE_WORKDONE )
        h->state.state = HB_STATE_IDLE;

    hb_unlock( h->state_lock );
}