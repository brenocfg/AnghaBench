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
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_BZ_RX_INGR_EN ; 
 int /*<<< orphan*/  FR_AZ_RX_CFG ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_drain_tx_fifo (struct efx_nic*) ; 

__attribute__((used)) static void falcon_deconfigure_mac_wrapper(struct efx_nic *efx)
{
	efx_oword_t reg;

	if (efx_nic_rev(efx) < EFX_REV_FALCON_B0)
		return;

	/* Isolate the MAC -> RX */
	efx_reado(efx, &reg, FR_AZ_RX_CFG);
	EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, 0);
	efx_writeo(efx, &reg, FR_AZ_RX_CFG);

	/* Isolate TX -> MAC */
	falcon_drain_tx_fifo(efx);
}