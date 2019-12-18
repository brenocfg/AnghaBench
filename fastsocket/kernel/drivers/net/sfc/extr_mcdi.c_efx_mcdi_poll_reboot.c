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
typedef  scalar_t__ uint32_t ;
struct efx_nic {int /*<<< orphan*/  mac_stats; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_DWORD_0 ; 
 scalar_t__ EFX_DWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_SIENA_A0 ; 
 int /*<<< orphan*/  EFX_ZERO_DWORD (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EIO ; 
 unsigned int FR_CZ_MC_TREG_SMEM ; 
 unsigned int MCDI_STATUS (struct efx_nic*) ; 
 scalar_t__ MC_STATUS_DWORD_ASSERT ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_readd (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int efx_mcdi_poll_reboot(struct efx_nic *efx)
{
	unsigned int addr = FR_CZ_MC_TREG_SMEM + MCDI_STATUS(efx);
	efx_dword_t reg;
	uint32_t value;

	if (efx_nic_rev(efx) < EFX_REV_SIENA_A0)
		return false;

	efx_readd(efx, &reg, addr);
	value = EFX_DWORD_FIELD(reg, EFX_DWORD_0);

	if (value == 0)
		return 0;

	/* MAC statistics have been cleared on the NIC; clear our copy
	 * so that efx_update_diff_stat() can continue to work.
	 */
	memset(&efx->mac_stats, 0, sizeof(efx->mac_stats));

	EFX_ZERO_DWORD(reg);
	efx_writed(efx, &reg, addr);

	if (value == MC_STATUS_DWORD_ASSERT)
		return -EINTR;
	else
		return -EIO;
}