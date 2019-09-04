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
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,int) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
sockv6_set_v6only(int s)
{
	int		on = 1;
	int		ret;

	ret = setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(ret, "setsockopt(%d, IPV6_ONLY)", s);
}