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
 int /*<<< orphan*/  br_ghash_ctmul32 ; 
 int /*<<< orphan*/  test_GHASH (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_GHASH_ctmul32(void)
{
	test_GHASH("GHASH_ctmul32", br_ghash_ctmul32);
}