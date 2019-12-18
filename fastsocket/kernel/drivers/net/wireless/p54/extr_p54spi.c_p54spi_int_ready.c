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
struct p54s_priv {int fw_state; int /*<<< orphan*/  fw_comp; } ;

/* Variables and functions */
#define  FW_STATE_BOOTING 129 
 void* FW_STATE_READY ; 
#define  FW_STATE_RESETTING 128 
 int /*<<< orphan*/  SPI_ADRS_HOST_INT_EN ; 
 int SPI_HOST_INT_SW_UPDATE ; 
 int SPI_HOST_INT_UPDATE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  p54spi_write32 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p54spi_int_ready(struct p54s_priv *priv)
{
	p54spi_write32(priv, SPI_ADRS_HOST_INT_EN, cpu_to_le32(
		       SPI_HOST_INT_UPDATE | SPI_HOST_INT_SW_UPDATE));

	switch (priv->fw_state) {
	case FW_STATE_BOOTING:
		priv->fw_state = FW_STATE_READY;
		complete(&priv->fw_comp);
		break;
	case FW_STATE_RESETTING:
		priv->fw_state = FW_STATE_READY;
		/* TODO: reinitialize state */
		break;
	default:
		break;
	}
}