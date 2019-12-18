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
typedef  int socklen_t ;

/* Variables and functions */
 int IFXNAMSIZ ; 
 int /*<<< orphan*/  SYSPROTO_CONTROL ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int,char*,...) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  g_OPT_IFNAME ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
tunsock_get_ifname(int s, char ifname[IFXNAMSIZ])
{
	socklen_t optlen = IFXNAMSIZ;
	T_QUIET; T_WITH_ERRNO; T_ASSERT_POSIX_ZERO(getsockopt(s, SYSPROTO_CONTROL, g_OPT_IFNAME, ifname, &optlen), NULL);
	T_QUIET; T_ASSERT_TRUE(optlen > 0, NULL);
	T_QUIET; T_ASSERT_TRUE(ifname[optlen-1] == '\0', NULL);
	T_QUIET; T_ASSERT_TRUE(strlen(ifname)+1 == optlen, "got ifname \"%s\" len %zd expected %u", ifname, strlen(ifname), optlen);
}