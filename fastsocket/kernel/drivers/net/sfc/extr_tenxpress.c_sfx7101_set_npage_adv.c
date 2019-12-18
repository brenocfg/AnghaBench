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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL_ADV10G ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  efx_mdio_set_flag (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sfx7101_set_npage_adv(struct efx_nic *efx, u32 advertising)
{
	efx_mdio_set_flag(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
			  MDIO_AN_10GBT_CTRL_ADV10G,
			  advertising & ADVERTISED_10000baseT_Full);
}