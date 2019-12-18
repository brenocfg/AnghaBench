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
struct x25_neigh {int state; } ;

/* Variables and functions */
#define  X25_LINK_STATE_0 129 
#define  X25_LINK_STATE_1 128 
 void* X25_LINK_STATE_2 ; 
 int /*<<< orphan*/  x25_start_t20timer (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_transmit_restart_request (struct x25_neigh*) ; 

void x25_link_established(struct x25_neigh *nb)
{
	switch (nb->state) {
		case X25_LINK_STATE_0:
			nb->state = X25_LINK_STATE_2;
			break;
		case X25_LINK_STATE_1:
			x25_transmit_restart_request(nb);
			nb->state = X25_LINK_STATE_2;
			x25_start_t20timer(nb);
			break;
	}
}