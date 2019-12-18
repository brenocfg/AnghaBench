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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_EXPECT_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  UINT64_C (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_fixed_counts(uint64_t counts[2][2])
{
	T_QUIET;
	T_EXPECT_GT(counts[0][0], UINT64_C(0), "instructions are larger than 0");
	T_QUIET;
	T_EXPECT_GT(counts[0][1], UINT64_C(0), "cycles are larger than 0");

	T_EXPECT_GT(counts[1][0], counts[0][0], "instructions increase monotonically");
	T_EXPECT_GT(counts[1][1], counts[0][1], "cycles increase monotonically");
}