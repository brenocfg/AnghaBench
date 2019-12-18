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
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_FAILURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ g_is_ipsec_test ; 
 int /*<<< orphan*/  g_pfkeyso ; 
 int /*<<< orphan*/  g_tunsock ; 

__attribute__((used)) static void
cleanup_tunsock(void)
{
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(g_tunsock), NULL);
	T_QUIET; T_EXPECT_POSIX_FAILURE(close(g_tunsock), EBADF, NULL);
	if (g_is_ipsec_test) {
		T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(close(g_pfkeyso), NULL);
		T_QUIET; T_EXPECT_POSIX_FAILURE(close(g_pfkeyso), EBADF, NULL);
	}
}