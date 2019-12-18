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
struct efx_mcdi_iface {int /*<<< orphan*/  state; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ MCDI_STATE_QUIESCENT ; 
 int /*<<< orphan*/  MCDI_STATE_RUNNING ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void efx_mcdi_acquire(struct efx_mcdi_iface *mcdi)
{
	/* Wait until the interface becomes QUIESCENT and we win the race
	 * to mark it RUNNING. */
	wait_event(mcdi->wq,
		   atomic_cmpxchg(&mcdi->state,
				  MCDI_STATE_QUIESCENT,
				  MCDI_STATE_RUNNING)
		   == MCDI_STATE_QUIESCENT);
}