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
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int /*<<< orphan*/ * br_ec_p256_m64_get () ; 
 int /*<<< orphan*/  br_secp256r1 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  test_speed_ec_inner (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_speed_ec_p256_m64(void)
{
	const br_ec_impl *ec;

	ec = br_ec_p256_m64_get();
	if (ec != NULL) {
		test_speed_ec_inner("EC p256_m64", ec, &br_secp256r1);
	} else {
		printf("%-30s UNAVAILABLE\n", "EC p256_m64");
	}
}