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
 scalar_t__ EFX_REV_SIENA_A0 ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int falcon_mtd_probe (struct efx_nic*) ; 
 int siena_mtd_probe (struct efx_nic*) ; 

int efx_mtd_probe(struct efx_nic *efx)
{
	if (efx_nic_rev(efx) >= EFX_REV_SIENA_A0)
		return siena_mtd_probe(efx);
	else
		return falcon_mtd_probe(efx);
}