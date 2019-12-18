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
 int EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FFE_AB_XX_STAT_ALL_LANES ; 
 int /*<<< orphan*/  FRF_AB_XX_ALIGN_DONE ; 
 int /*<<< orphan*/  FRF_AB_XX_CHAR_ERR ; 
 int /*<<< orphan*/  FRF_AB_XX_COMMA_DET ; 
 int /*<<< orphan*/  FRF_AB_XX_DISPERR ; 
 int /*<<< orphan*/  FRF_AB_XX_SYNC_STAT ; 
 int /*<<< orphan*/  FR_AB_XX_CORE_STAT ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool falcon_xgxs_link_ok(struct efx_nic *efx)
{
	efx_oword_t reg;
	bool align_done, link_ok = false;
	int sync_status;

	/* Read link status */
	efx_reado(efx, &reg, FR_AB_XX_CORE_STAT);

	align_done = EFX_OWORD_FIELD(reg, FRF_AB_XX_ALIGN_DONE);
	sync_status = EFX_OWORD_FIELD(reg, FRF_AB_XX_SYNC_STAT);
	if (align_done && (sync_status == FFE_AB_XX_STAT_ALL_LANES))
		link_ok = true;

	/* Clear link status ready for next read */
	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_COMMA_DET, FFE_AB_XX_STAT_ALL_LANES);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_CHAR_ERR, FFE_AB_XX_STAT_ALL_LANES);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_DISPERR, FFE_AB_XX_STAT_ALL_LANES);
	efx_writeo(efx, &reg, FR_AB_XX_CORE_STAT);

	return link_ok;
}