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
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;

/* Variables and functions */
 int RESET_TYPE_WORLD ; 
 int efx_mcdi_handle_assertion (struct efx_nic*) ; 
 int efx_mcdi_reset_mc (struct efx_nic*) ; 
 int efx_mcdi_reset_port (struct efx_nic*) ; 

__attribute__((used)) static int siena_reset_hw(struct efx_nic *efx, enum reset_type method)
{
	int rc;

	/* Recover from a failed assertion pre-reset */
	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		return rc;

	if (method == RESET_TYPE_WORLD)
		return efx_mcdi_reset_mc(efx);
	else
		return efx_mcdi_reset_port(efx);
}