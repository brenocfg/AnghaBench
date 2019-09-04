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
 int /*<<< orphan*/  T_EXPECT_GE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  close (int) ; 
 int create_tunsock (int,int,int) ; 

__attribute__((used)) static void
permute_enables(void)
{
	int tunsock;
	T_EXPECT_GE(tunsock = create_tunsock(false, false, false), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(false, false, true), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(false, true, false), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(false, true, true), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(true, false, false), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(true, false, true), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(true, true, false), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
	T_EXPECT_GE(tunsock = create_tunsock(true, true, true), 0, NULL);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(tunsock), NULL);
}