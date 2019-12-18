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

/* Variables and functions */
 int BR_EC_curve25519 ; 
 int /*<<< orphan*/  br_ec_c25519_i31 ; 
 int /*<<< orphan*/  test_EC_c25519 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_EC_keygen (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
test_EC_c25519_i31(void)
{
	test_EC_c25519("EC_c25519_i31", &br_ec_c25519_i31);
	test_EC_keygen("EC_c25519_i31", &br_ec_c25519_i31,
		(uint32_t)1 << BR_EC_curve25519);
}