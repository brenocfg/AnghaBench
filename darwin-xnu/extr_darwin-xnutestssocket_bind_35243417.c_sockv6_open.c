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
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sockv6_open(void)
{
	int	s;

	s = socket(AF_INET6, SOCK_DGRAM, 0);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(s, "socket(AF_INET6, SOCK_DGRAM, 0)");
	return (s);
}