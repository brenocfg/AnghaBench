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
struct efx_mcdi_request {int len; scalar_t__ cmd; int rc; scalar_t__ payload; } ;
union efx_ioctl_data {struct efx_mcdi_request mcdi_request; } ;
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ EFX_REV_SIENA_A0 ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTSUPP ; 
 scalar_t__ MC_CMD_REBOOT ; 
 int /*<<< orphan*/  RESET_TYPE_MC_FAILURE ; 
 int /*<<< orphan*/  drv ; 
 int efx_mcdi_rpc (struct efx_nic*,scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int efx_ioctl_do_mcdi(struct efx_nic *efx, union efx_ioctl_data *data)
{
	struct efx_mcdi_request *req = &data->mcdi_request;
	size_t outlen;
	int rc;

	if (req->len > sizeof(req->payload) || req->len & 3) {
		netif_err(efx, drv, efx->net_dev, "inlen is too long");
		return -EINVAL;
	}

	if (efx_nic_rev(efx) < EFX_REV_SIENA_A0) {
		netif_err(efx, drv, efx->net_dev,
			  "error: NIC has no MC for MCDI\n");
		return -ENOTSUPP;
	}

	rc = efx_mcdi_rpc(efx, req->cmd, (const u8 *)req->payload,
			  req->len, (u8 *)req->payload,
			  sizeof(req->payload), &outlen);

	/* efx_mcdi_rpc() will not schedule a reset if MC_CMD_PAYLOAD causes
	 * a reboot. But from the user's POV, they're triggering a reboot
	 * 'externally', and want both ports to recover. So schedule the
	 * reset here
	 */
	if (req->cmd == MC_CMD_REBOOT && rc == -EIO) {
		netif_err(efx, drv, efx->net_dev, "MC fatal error %d\n", -rc);
		efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
	}

	/* No distinction is made between RPC failures (driver timeouts) and
	 * MCDI failures (timeouts, reboots etc)
	 */
	req->rc = -rc;
	req->len = (__u8)outlen;
	return 0;
}