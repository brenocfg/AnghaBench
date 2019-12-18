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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int BR_EC_curve25519 ; 
 int /*<<< orphan*/ * br_ec_c25519_m64_get () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_EC_c25519 (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_EC_keygen (char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
test_EC_c25519_m64(void)
{
	const br_ec_impl *ec;

	ec = br_ec_c25519_m64_get();
	if (ec != NULL) {
		test_EC_c25519("EC_c25519_m64", ec);
		test_EC_keygen("EC_c25519_m64", ec,
			(uint32_t)1 << BR_EC_curve25519);
	} else {
		printf("Test EC_c25519_m64: UNAVAILABLE\n");
		printf("Test EC_c25519_m64 keygen: UNAVAILABLE\n");
	}
}