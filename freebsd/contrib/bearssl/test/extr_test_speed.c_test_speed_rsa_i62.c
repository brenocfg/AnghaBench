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
typedef  scalar_t__ br_rsa_public ;
typedef  int /*<<< orphan*/  br_rsa_private ;
typedef  int /*<<< orphan*/  br_rsa_keygen ;

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i62_keygen_get () ; 
 int /*<<< orphan*/  br_rsa_i62_private_get () ; 
 scalar_t__ br_rsa_i62_public_get () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  test_speed_rsa_inner (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_speed_rsa_i62(void)
{
	br_rsa_public pub;
	br_rsa_private priv;
	br_rsa_keygen kgen;

	pub = br_rsa_i62_public_get();
	priv = br_rsa_i62_private_get();
	kgen = br_rsa_i62_keygen_get();
	if (pub) {
		test_speed_rsa_inner("RSA i62", pub, priv, kgen);
	} else {
		printf("%-30s UNAVAILABLE\n", "RSA i62");
	}
}