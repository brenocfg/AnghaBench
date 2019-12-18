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
 int EBUSY ; 
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AB_EE_SPI_HCMD_CMD_EN ; 
 int /*<<< orphan*/  FR_AB_EE_SPI_HCMD ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int falcon_spi_poll(struct efx_nic *efx)
{
	efx_oword_t reg;
	efx_reado(efx, &reg, FR_AB_EE_SPI_HCMD);
	return EFX_OWORD_FIELD(reg, FRF_AB_EE_SPI_HCMD_CMD_EN) ? -EBUSY : 0;
}