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
 int /*<<< orphan*/  br_ghash_ctmul ; 
 int /*<<< orphan*/  test_speed_ghash_inner (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_speed_ghash_ctmul(void)
{
	test_speed_ghash_inner("GHASH (ctmul)", &br_ghash_ctmul);
}