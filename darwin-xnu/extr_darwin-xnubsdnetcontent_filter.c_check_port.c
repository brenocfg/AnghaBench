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
typedef  scalar_t__ u_short ;
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct sockaddr_in* satosin (struct sockaddr*) ; 
 struct sockaddr_in6* satosin6 (struct sockaddr*) ; 

bool
check_port(struct sockaddr *addr, u_short port)
{
	struct sockaddr_in *sin = NULL;
	struct sockaddr_in6 *sin6 = NULL;

	if (addr == NULL || port == 0) {
		return FALSE;
	}

	switch (addr->sa_family) {
		case AF_INET:
			sin = satosin(addr);
			if (sin->sin_len != sizeof(*sin)) {
				return FALSE;
			}
			if (port == ntohs(sin->sin_port)) {
				return TRUE;
			}
			break;
		case AF_INET6:
			sin6 = satosin6(addr);
			if (sin6->sin6_len != sizeof(*sin6)) {
				return FALSE;
			}
			if (port == ntohs(sin6->sin6_port)) {
				return TRUE;
			}
			break;
		default:
			break;
	}
	return FALSE;
}