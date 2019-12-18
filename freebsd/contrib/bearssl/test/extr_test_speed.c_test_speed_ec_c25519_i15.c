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

/* Variables and functions */
 int /*<<< orphan*/  br_curve25519 ; 
 int /*<<< orphan*/  br_ec_c25519_i15 ; 
 int /*<<< orphan*/  test_speed_ec_inner (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_speed_ec_c25519_i15(void)
{
	test_speed_ec_inner("EC c25519_i15",
		&br_ec_c25519_i15, &br_curve25519);
}