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
struct efx_nic {int /*<<< orphan*/ * rx_indir_table; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  FRF_BZ_IT_QUEUE ; 
 scalar_t__ FR_BZ_RX_INDIRECTION_TBL ; 
 size_t FR_BZ_RX_INDIRECTION_TBL_ROWS ; 
 size_t FR_BZ_RX_INDIRECTION_TBL_STEP ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/ *,scalar_t__) ; 

void efx_nic_push_rx_indir_table(struct efx_nic *efx)
{
	size_t i = 0;
	efx_dword_t dword;

	if (efx_nic_rev(efx) < EFX_REV_FALCON_B0)
		return;

	BUILD_BUG_ON(ARRAY_SIZE(efx->rx_indir_table) !=
		     FR_BZ_RX_INDIRECTION_TBL_ROWS);

	for (i = 0; i < FR_BZ_RX_INDIRECTION_TBL_ROWS; i++) {
		EFX_POPULATE_DWORD_1(dword, FRF_BZ_IT_QUEUE,
				     efx->rx_indir_table[i]);
		efx_writed(efx, &dword,
			   FR_BZ_RX_INDIRECTION_TBL +
			   FR_BZ_RX_INDIRECTION_TBL_STEP * i);
	}
}