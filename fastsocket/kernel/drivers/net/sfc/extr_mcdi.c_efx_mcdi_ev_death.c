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
struct efx_mcdi_iface {scalar_t__ mode; int resprc; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  credits; scalar_t__ resplen; } ;

/* Variables and functions */
 scalar_t__ MCDI_MODE_EVENTS ; 
 int MCDI_STATUS_DELAY_COUNT ; 
 int /*<<< orphan*/  MCDI_STATUS_DELAY_US ; 
 int /*<<< orphan*/  RESET_TYPE_MC_FAILURE ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 scalar_t__ efx_mcdi_complete (struct efx_mcdi_iface*) ; 
 scalar_t__ efx_mcdi_poll_reboot (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_mcdi_ev_death(struct efx_nic *efx, int rc)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	/* If there is an outstanding MCDI request, it has been terminated
	 * either by a BADASSERT or REBOOT event. If the mcdi interface is
	 * in polled mode, then do nothing because the MC reboot handler will
	 * set the header correctly. However, if the mcdi interface is waiting
	 * for a CMDDONE event it won't receive it [and since all MCDI events
	 * are sent to the same queue, we can't be racing with
	 * efx_mcdi_ev_cpl()]
	 *
	 * There's a race here with efx_mcdi_rpc(), because we might receive
	 * a REBOOT event *before* the request has been copied out. In polled
	 * mode (during startup) this is irrelevant, because efx_mcdi_complete()
	 * is ignored. In event mode, this condition is just an edge-case of
	 * receiving a REBOOT event after posting the MCDI request. Did the mc
	 * reboot before or after the copyout? The best we can do always is
	 * just return failure.
	 */
	spin_lock(&mcdi->iface_lock);
	if (efx_mcdi_complete(mcdi)) {
		if (mcdi->mode == MCDI_MODE_EVENTS) {
			mcdi->resprc = rc;
			mcdi->resplen = 0;
			++mcdi->credits;
		}
	} else {
		int count;

		/* Nobody was waiting for an MCDI request, so trigger a reset */
		efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);

		/* Consume the status word since efx_mcdi_rpc_finish() won't */
		for (count = 0; count < MCDI_STATUS_DELAY_COUNT; ++count) {
			if (efx_mcdi_poll_reboot(efx))
				break;
			udelay(MCDI_STATUS_DELAY_US);
		}
	}

	spin_unlock(&mcdi->iface_lock);
}