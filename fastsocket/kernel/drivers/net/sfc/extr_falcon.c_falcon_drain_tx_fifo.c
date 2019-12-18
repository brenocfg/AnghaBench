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
struct efx_nic {scalar_t__ loopback_mode; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  FRF_BB_TXFIFO_DRAIN_EN ; 
 int /*<<< orphan*/  FR_AB_MAC_CTRL ; 
 scalar_t__ LOOPBACK_NONE ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_reset_macs (struct efx_nic*) ; 

void falcon_drain_tx_fifo(struct efx_nic *efx)
{
	efx_oword_t reg;

	if ((efx_nic_rev(efx) < EFX_REV_FALCON_B0) ||
	    (efx->loopback_mode != LOOPBACK_NONE))
		return;

	efx_reado(efx, &reg, FR_AB_MAC_CTRL);
	/* There is no point in draining more than once */
	if (EFX_OWORD_FIELD(reg, FRF_BB_TXFIFO_DRAIN_EN))
		return;

	falcon_reset_macs(efx);
}