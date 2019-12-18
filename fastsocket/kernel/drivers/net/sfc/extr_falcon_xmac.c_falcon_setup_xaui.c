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
struct efx_nic {scalar_t__ phy_type; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFE_AB_XX_SD_CTL_DRV_DEF ; 
 int /*<<< orphan*/  FFE_AB_XX_TXDRV_DEQ_DEF ; 
 int /*<<< orphan*/  FFE_AB_XX_TXDRV_DTX_DEF ; 
 int /*<<< orphan*/  FRF_AB_XX_DEQA ; 
 int /*<<< orphan*/  FRF_AB_XX_DEQB ; 
 int /*<<< orphan*/  FRF_AB_XX_DEQC ; 
 int /*<<< orphan*/  FRF_AB_XX_DEQD ; 
 int /*<<< orphan*/  FRF_AB_XX_DTXA ; 
 int /*<<< orphan*/  FRF_AB_XX_DTXB ; 
 int /*<<< orphan*/  FRF_AB_XX_DTXC ; 
 int /*<<< orphan*/  FRF_AB_XX_DTXD ; 
 int /*<<< orphan*/  FRF_AB_XX_HIDRVA ; 
 int /*<<< orphan*/  FRF_AB_XX_HIDRVB ; 
 int /*<<< orphan*/  FRF_AB_XX_HIDRVC ; 
 int /*<<< orphan*/  FRF_AB_XX_HIDRVD ; 
 int /*<<< orphan*/  FRF_AB_XX_LODRVA ; 
 int /*<<< orphan*/  FRF_AB_XX_LODRVB ; 
 int /*<<< orphan*/  FRF_AB_XX_LODRVC ; 
 int /*<<< orphan*/  FRF_AB_XX_LODRVD ; 
 int /*<<< orphan*/  FR_AB_XX_SD_CTL ; 
 int /*<<< orphan*/  FR_AB_XX_TXDRV_CTL ; 
 scalar_t__ PHY_TYPE_NONE ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void falcon_setup_xaui(struct efx_nic *efx)
{
	efx_oword_t sdctl, txdrv;

	/* Move the XAUI into low power, unless there is no PHY, in
	 * which case the XAUI will have to drive a cable. */
	if (efx->phy_type == PHY_TYPE_NONE)
		return;

	efx_reado(efx, &sdctl, FR_AB_XX_SD_CTL);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVD, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVD, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVC, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVC, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVB, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVB, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVA, FFE_AB_XX_SD_CTL_DRV_DEF);
	EFX_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVA, FFE_AB_XX_SD_CTL_DRV_DEF);
	efx_writeo(efx, &sdctl, FR_AB_XX_SD_CTL);

	EFX_POPULATE_OWORD_8(txdrv,
			     FRF_AB_XX_DEQD, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQC, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQB, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQA, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DTXD, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXC, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXB, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXA, FFE_AB_XX_TXDRV_DTX_DEF);
	efx_writeo(efx, &txdrv, FR_AB_XX_TXDRV_CTL);
}