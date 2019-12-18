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
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {scalar_t__ mode; int resprc; size_t resplen; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  credits; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EFX_REV_SIENA_A0 ; 
 int EINTR ; 
 int EIO ; 
 scalar_t__ MCDI_MODE_POLL ; 
 int /*<<< orphan*/  MCDI_STATUS_SLEEP_MS ; 
 unsigned int MC_CMD_REBOOT ; 
 int /*<<< orphan*/  RESET_TYPE_MC_FAILURE ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int efx_mcdi_await_completion (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_copyout (struct efx_nic*,int /*<<< orphan*/ *,int) ; 
 int efx_mcdi_poll (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_poll_reboot (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_release (struct efx_mcdi_iface*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int min (size_t,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int efx_mcdi_rpc_finish(struct efx_nic *efx, unsigned cmd, size_t inlen,
			u8 *outbuf, size_t outlen, size_t *outlen_actual)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	int rc;

	BUG_ON(efx_nic_rev(efx) < EFX_REV_SIENA_A0);

	if (mcdi->mode == MCDI_MODE_POLL)
		rc = efx_mcdi_poll(efx);
	else
		rc = efx_mcdi_await_completion(efx);

	if (rc != 0) {
		/* Close the race with efx_mcdi_ev_cpl() executing just too late
		 * and completing a request we've just cancelled, by ensuring
		 * that the seqno check therein fails.
		 */
		spin_lock_bh(&mcdi->iface_lock);
		++mcdi->seqno;
		++mcdi->credits;
		spin_unlock_bh(&mcdi->iface_lock);

		netif_err(efx, hw, efx->net_dev,
			  "MC command 0x%x inlen %d mode %d timed out\n",
			  cmd, (int)inlen, mcdi->mode);
	} else {
		size_t resplen;

		/* At the very least we need a memory barrier here to ensure
		 * we pick up changes from efx_mcdi_ev_cpl(). Protect against
		 * a spurious efx_mcdi_ev_cpl() running concurrently by
		 * acquiring the iface_lock. */
		spin_lock_bh(&mcdi->iface_lock);
		rc = -mcdi->resprc;
		resplen = mcdi->resplen;
		spin_unlock_bh(&mcdi->iface_lock);

		if (rc == 0) {
			efx_mcdi_copyout(efx, outbuf,
					 min(outlen, mcdi->resplen + 3) & ~0x3);
			if (outlen_actual != NULL)
				*outlen_actual = resplen;
		} else if (cmd == MC_CMD_REBOOT && rc == -EIO)
			; /* Don't reset if MC_CMD_REBOOT returns EIO */
		else if (rc == -EIO || rc == -EINTR) {
			netif_err(efx, hw, efx->net_dev, "MC fatal error %d\n",
				  -rc);
			efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
		} else
			netif_dbg(efx, hw, efx->net_dev,
				  "MC command 0x%x inlen %d failed rc=%d\n",
				  cmd, (int)inlen, -rc);

		if (rc == -EIO || rc == -EINTR) {
			msleep(MCDI_STATUS_SLEEP_MS);
			efx_mcdi_poll_reboot(efx);
		}
	}

	efx_mcdi_release(mcdi);
	return rc;
}