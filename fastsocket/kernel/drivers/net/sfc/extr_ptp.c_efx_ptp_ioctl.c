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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int dummy; } ;
struct efx_nic {int /*<<< orphan*/  ptp_data; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int efx_ptp_ts_init (struct efx_nic*,struct hwtstamp_config*) ; 

int efx_ptp_ioctl(struct efx_nic *efx, struct ifreq *ifr, int cmd)
{
	struct hwtstamp_config config;
	int rc;

	/* Not a PTP enabled port */
	if (!efx->ptp_data)
		return -EOPNOTSUPP;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	rc = efx_ptp_ts_init(efx, &config);
	if (rc != 0)
		return rc;

	return copy_to_user(ifr->ifr_data, &config, sizeof(config))
		? -EFAULT : 0;
}