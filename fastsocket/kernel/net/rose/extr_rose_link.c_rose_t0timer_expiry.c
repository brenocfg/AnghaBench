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
struct rose_neigh {scalar_t__ dce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  rose_start_t0timer (struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_transmit_restart_request (struct rose_neigh*) ; 

__attribute__((used)) static void rose_t0timer_expiry(unsigned long param)
{
	struct rose_neigh *neigh = (struct rose_neigh *)param;

	rose_transmit_restart_request(neigh);

	neigh->dce_mode = 0;

	rose_start_t0timer(neigh);
}