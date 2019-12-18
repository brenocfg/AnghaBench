#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_port; } ;
union sockaddr_in_4_6 {TYPE_3__ sa; TYPE_2__ sin6; TYPE_1__ sin; } ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,int) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int,char*,int) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  bzero (union sockaddr_in_4_6*,int) ; 
 int getsockname (int,struct sockaddr*,int*) ; 

__attribute__((used)) static uint16_t
sock_get_port(int sockfd)
{
	int				error;
	uint16_t			p;
	union sockaddr_in_4_6 	sin;
	socklen_t			sin_len;

	sin_len = sizeof(sin);
	bzero(&sin, sin_len);
	error = getsockname(sockfd, (struct sockaddr *)&sin, &sin_len);
	T_QUIET;
	T_EXPECT_POSIX_ZERO(error, "getsockname(%d)", sockfd);
	if (error != 0) {
		return (0);
	}
	switch (sin.sa.sa_family) {
	case AF_INET:
		p = sin.sin.sin_port;
		break;
	case AF_INET6:
		p = sin.sin6.sin6_port;
		break;
	default:
		T_ASSERT_FAIL("unknown address family %d\n",
			      sin.sa.sa_family);
		p = 0;
		break;
	}
	return (p);
}