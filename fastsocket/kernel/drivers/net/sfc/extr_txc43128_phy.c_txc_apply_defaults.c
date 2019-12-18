#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int dummy; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_phy ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  TXC_ALRGS_ATXAMP0 ; 
 int /*<<< orphan*/  TXC_ALRGS_ATXAMP1 ; 
 int /*<<< orphan*/  TXC_ALRGS_ATXPRE0 ; 
 int /*<<< orphan*/  TXC_ALRGS_ATXPRE1 ; 
 int TXC_ATXAMP_0820_BOTH ; 
 int TXC_ATXAMP_DEFAULT ; 
 int TXC_ATXPRE_DEFAULT ; 
 int TXC_ATXPRE_NONE ; 
 int TXC_MCTL_RXLED_LBN ; 
 int TXC_MCTL_TXLED_LBN ; 
 int /*<<< orphan*/  TXC_MRGS_CTL ; 
 int efx_mdio_read (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mdio_write (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  txc_reset_logic (struct efx_nic*) ; 

__attribute__((used)) static void txc_apply_defaults(struct efx_nic *efx)
{
	int mctrl;

	/* Turn amplitude down and preemphasis off on the host side
	 * (PHY<->MAC) as this is believed less likely to upset Falcon
	 * and no adverse effects have been noted. It probably also
	 * saves a picowatt or two */

	/* Turn off preemphasis */
	efx_mdio_write(efx, MDIO_MMD_PHYXS, TXC_ALRGS_ATXPRE0, TXC_ATXPRE_NONE);
	efx_mdio_write(efx, MDIO_MMD_PHYXS, TXC_ALRGS_ATXPRE1, TXC_ATXPRE_NONE);

	/* Turn down the amplitude */
	efx_mdio_write(efx, MDIO_MMD_PHYXS,
		       TXC_ALRGS_ATXAMP0, TXC_ATXAMP_0820_BOTH);
	efx_mdio_write(efx, MDIO_MMD_PHYXS,
		       TXC_ALRGS_ATXAMP1, TXC_ATXAMP_0820_BOTH);

	/* Set the line side amplitude and preemphasis to the databook
	 * defaults as an erratum causes them to be 0 on at least some
	 * PHY rev.s */
	efx_mdio_write(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXPRE0, TXC_ATXPRE_DEFAULT);
	efx_mdio_write(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXPRE1, TXC_ATXPRE_DEFAULT);
	efx_mdio_write(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXAMP0, TXC_ATXAMP_DEFAULT);
	efx_mdio_write(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXAMP1, TXC_ATXAMP_DEFAULT);

	/* Set up the LEDs  */
	mctrl = efx_mdio_read(efx, MDIO_MMD_PHYXS, TXC_MRGS_CTL);

	/* Set the Green and Red LEDs to their default modes */
	mctrl &= ~((1 << TXC_MCTL_TXLED_LBN) | (1 << TXC_MCTL_RXLED_LBN));
	efx_mdio_write(efx, MDIO_MMD_PHYXS, TXC_MRGS_CTL, mctrl);

	/* Databook recommends doing this after configuration changes */
	txc_reset_logic(efx);

	falcon_board(efx)->type->init_phy(efx);
}