#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qt202x_phy_data {int bug17190_in_bad_state; scalar_t__ bug17190_timer; int /*<<< orphan*/  phy_mode; } ;
struct TYPE_2__ {int mode_support; int /*<<< orphan*/  mmds; } ;
struct efx_nic {int loopback_modes; TYPE_1__ mdio; int /*<<< orphan*/  phy_mode; struct qt202x_phy_data* phy_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FALCON_XMAC_LOOPBACKS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MDIO_EMULATE_C22 ; 
 int MDIO_SUPPORTS_C45 ; 
 int QT202X_LOOPBACKS ; 
 int /*<<< orphan*/  QT202X_REQUIRED_DEVS ; 
 struct qt202x_phy_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt202x_phy_probe(struct efx_nic *efx)
{
	struct qt202x_phy_data *phy_data;

	phy_data = kzalloc(sizeof(struct qt202x_phy_data), GFP_KERNEL);
	if (!phy_data)
		return -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;
	phy_data->bug17190_in_bad_state = false;
	phy_data->bug17190_timer = 0;

	efx->mdio.mmds = QT202X_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	efx->loopback_modes = QT202X_LOOPBACKS | FALCON_XMAC_LOOPBACKS;
	return 0;
}