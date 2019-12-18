#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int so_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKEV_CONNECTED ; 
 int /*<<< orphan*/  SOCKEV_DISCONNECTED ; 
 int SS_ISCONNECTED ; 
 int SS_ISDISCONNECTED ; 

void
get_sockev_state(struct socket *so, u_int32_t *statep)
{
	u_int32_t state = *(statep);

	/*
	 * If the state variable is already used by a previous event,
	 * reset it.
	 */
	if (state != 0)
		return;

	if (so->so_state & SS_ISCONNECTED)
		state |= SOCKEV_CONNECTED;
	else
		state &= ~(SOCKEV_CONNECTED);
	state |= ((so->so_state & SS_ISDISCONNECTED) ? SOCKEV_DISCONNECTED : 0);
	*(statep) = state;
}