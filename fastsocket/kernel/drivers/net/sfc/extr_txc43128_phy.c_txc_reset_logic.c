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

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  txc_reset_logic_mmd (struct efx_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void txc_reset_logic(struct efx_nic *efx)
{
	/* The data sheet claims we can do the logic reset on either the
	 * PCS or the PHYXS and the result is a reset of both host- and
	 * line-side logic. */
	txc_reset_logic_mmd(efx, MDIO_MMD_PCS);
}