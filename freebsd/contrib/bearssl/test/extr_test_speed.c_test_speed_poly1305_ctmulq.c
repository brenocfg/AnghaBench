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
typedef  scalar_t__ br_poly1305_run ;

/* Variables and functions */
 scalar_t__ br_poly1305_ctmulq_get () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  test_speed_poly1305_inner (char*,scalar_t__) ; 

__attribute__((used)) static void
test_speed_poly1305_ctmulq(void)
{
	br_poly1305_run bp;

	bp = br_poly1305_ctmulq_get();
	if (bp == 0) {
		printf("%-30s UNAVAILABLE\n", "Poly1305 (ctmulq)");
	} else {
		test_speed_poly1305_inner("Poly1305 (ctmulq)", bp);
	}
}