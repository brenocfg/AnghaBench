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
 int /*<<< orphan*/  br_rsa_i15_keygen ; 
 int /*<<< orphan*/  br_rsa_i15_private ; 
 int /*<<< orphan*/  br_rsa_i15_public ; 
 int /*<<< orphan*/  test_speed_rsa_inner (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_speed_rsa_i15(void)
{
	test_speed_rsa_inner("RSA i15",
		&br_rsa_i15_public, &br_rsa_i15_private, &br_rsa_i15_keygen);
}