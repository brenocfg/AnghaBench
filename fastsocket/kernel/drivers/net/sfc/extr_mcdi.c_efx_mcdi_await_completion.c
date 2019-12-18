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
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {scalar_t__ mode; int /*<<< orphan*/  state; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MCDI_MODE_POLL ; 
 int /*<<< orphan*/  MCDI_RPC_TIMEOUT ; 
 scalar_t__ MCDI_STATE_COMPLETED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int efx_mcdi_poll (struct efx_nic*) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_mcdi_await_completion(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	if (wait_event_timeout(
		    mcdi->wq,
		    atomic_read(&mcdi->state) == MCDI_STATE_COMPLETED,
		    MCDI_RPC_TIMEOUT) == 0)
		return -ETIMEDOUT;

	/* Check if efx_mcdi_set_mode() switched us back to polled completions.
	 * In which case, poll for completions directly. If efx_mcdi_ev_cpl()
	 * completed the request first, then we'll just end up completing the
	 * request again, which is safe.
	 *
	 * We need an smp_rmb() to synchronise with efx_mcdi_mode_poll(), which
	 * wait_event_timeout() implicitly provides.
	 */
	if (mcdi->mode == MCDI_MODE_POLL)
		return efx_mcdi_poll(efx);

	return 0;
}