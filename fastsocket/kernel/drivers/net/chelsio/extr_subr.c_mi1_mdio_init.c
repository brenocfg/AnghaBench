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
typedef  int u32 ;
struct board_info {int clock_elmer0; int mdio_mdc; int caps; int /*<<< orphan*/  mdio_mdien; int /*<<< orphan*/  mdio_mdiinv; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_PORT0_MI1_CFG ; 
 int F_MI1_PREAMBLE_ENABLE ; 
 int SUPPORTED_10000baseT_Full ; 
 int V_MI1_CLK_DIV (int) ; 
 int V_MI1_MDI_ENABLE (int /*<<< orphan*/ ) ; 
 int V_MI1_MDI_INVERT (int /*<<< orphan*/ ) ; 
 int V_MI1_SOF (int) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mi1_mdio_init(adapter_t *adapter, const struct board_info *bi)
{
	u32 clkdiv = bi->clock_elmer0 / (2 * bi->mdio_mdc) - 1;
	u32 val = F_MI1_PREAMBLE_ENABLE | V_MI1_MDI_INVERT(bi->mdio_mdiinv) |
		V_MI1_MDI_ENABLE(bi->mdio_mdien) | V_MI1_CLK_DIV(clkdiv);

	if (!(bi->caps & SUPPORTED_10000baseT_Full))
		val |= V_MI1_SOF(1);
	t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_CFG, val);
}