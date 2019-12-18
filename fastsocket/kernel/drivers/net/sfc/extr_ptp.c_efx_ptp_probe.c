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
struct efx_nic {int /*<<< orphan*/ ** extra_channel_type; } ;

/* Variables and functions */
 size_t EFX_EXTRA_CHANNEL_PTP ; 
 int /*<<< orphan*/  efx_ptp_channel_type ; 
 scalar_t__ efx_ptp_disable (struct efx_nic*) ; 

void efx_ptp_probe(struct efx_nic *efx)
{
	/* Check whether PTP is implemented on this NIC.  The DISABLE
	 * operation will succeed if and only if it is implemented.
	 */
	if (efx_ptp_disable(efx) == 0)
		efx->extra_channel_type[EFX_EXTRA_CHANNEL_PTP] =
			&efx_ptp_channel_type;
}