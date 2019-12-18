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
struct x25_neigh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  x25_start_t20timer (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_transmit_restart_request (struct x25_neigh*) ; 

__attribute__((used)) static void x25_t20timer_expiry(unsigned long param)
{
	struct x25_neigh *nb = (struct x25_neigh *)param;

	x25_transmit_restart_request(nb);

	x25_start_t20timer(nb);
}