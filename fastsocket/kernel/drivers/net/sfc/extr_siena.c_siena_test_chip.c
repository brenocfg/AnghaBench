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
struct efx_self_tests {int registers; } ;
struct efx_nic {int dummy; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int RESET_TYPE_ALL ; 
 scalar_t__ efx_nic_test_registers (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_reset_down (struct efx_nic*,int) ; 
 int efx_reset_up (struct efx_nic*,int,int) ; 
 int /*<<< orphan*/  siena_register_tests ; 
 int siena_reset_hw (struct efx_nic*,int) ; 

__attribute__((used)) static int siena_test_chip(struct efx_nic *efx, struct efx_self_tests *tests)
{
	enum reset_type reset_method = RESET_TYPE_ALL;
	int rc, rc2;

	efx_reset_down(efx, reset_method);

	/* Reset the chip immediately so that it is completely
	 * quiescent regardless of what any VF driver does.
	 */
	rc = siena_reset_hw(efx, reset_method);
	if (rc)
		goto out;

	tests->registers =
		efx_nic_test_registers(efx, siena_register_tests,
				       ARRAY_SIZE(siena_register_tests))
		? -1 : 1;

	rc = siena_reset_hw(efx, reset_method);
out:
	rc2 = efx_reset_up(efx, reset_method, rc == 0);
	return rc ? rc : rc2;
}