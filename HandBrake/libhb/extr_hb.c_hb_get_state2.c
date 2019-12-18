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
typedef  int /*<<< orphan*/  hb_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void hb_get_state2( hb_handle_t * h, hb_state_t * s )
{
    hb_lock( h->state_lock );

    memcpy( s, &h->state, sizeof( hb_state_t ) );

    hb_unlock( h->state_lock );
}