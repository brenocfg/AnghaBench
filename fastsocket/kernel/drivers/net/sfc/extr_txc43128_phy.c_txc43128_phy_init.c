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
 int /*<<< orphan*/  txc_apply_defaults (struct efx_nic*) ; 
 int txc_bist (struct efx_nic*) ; 
 int txc_reset_phy (struct efx_nic*) ; 

__attribute__((used)) static int txc43128_phy_init(struct efx_nic *efx)
{
	int rc;

	rc = txc_reset_phy(efx);
	if (rc < 0)
		return rc;

	rc = txc_bist(efx);
	if (rc < 0)
		return rc;

	txc_apply_defaults(efx);

	return 0;
}