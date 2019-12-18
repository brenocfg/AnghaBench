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
 int BR_EC_secp256r1 ; 
 int /*<<< orphan*/  br_ec_p256_m15 ; 
 int /*<<< orphan*/  test_EC_KAT (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_EC_keygen (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
test_EC_p256_m15(void)
{
	test_EC_KAT("EC_p256_m15", &br_ec_p256_m15,
		(uint32_t)1 << BR_EC_secp256r1);
	test_EC_keygen("EC_p256_m15", &br_ec_p256_m15,
		(uint32_t)1 << BR_EC_secp256r1);
}