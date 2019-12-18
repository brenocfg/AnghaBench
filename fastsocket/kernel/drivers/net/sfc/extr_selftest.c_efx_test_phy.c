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
struct efx_self_tests {int /*<<< orphan*/  phy_ext; } ;
struct efx_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; } ;
struct TYPE_2__ {int (* run_tests ) (struct efx_nic*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct efx_nic*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int efx_test_phy(struct efx_nic *efx, struct efx_self_tests *tests,
			unsigned flags)
{
	int rc;

	if (!efx->phy_op->run_tests)
		return 0;

	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->run_tests(efx, tests->phy_ext, flags);
	mutex_unlock(&efx->mac_lock);
	return rc;
}