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
typedef  scalar_t__ br_ghash ;

/* Variables and functions */
 scalar_t__ br_ghash_pwr8_get () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_GHASH (char*,scalar_t__) ; 

__attribute__((used)) static void
test_GHASH_pwr8(void)
{
	br_ghash gh;

	gh = br_ghash_pwr8_get();
	if (gh == 0) {
		printf("Test GHASH_pwr8: UNAVAILABLE\n");
	} else {
		test_GHASH("GHASH_pwr8", gh);
	}
}