#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int FALSE ; 
 int IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_LOOPBACK ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_addr_is_loopback(struct sockaddr *address)
{
	if (address == NULL) {
		return (FALSE);
	}

	if (address->sa_family == AF_INET) {
		return (ntohl(((struct sockaddr_in *)(void *)address)->sin_addr.s_addr) == INADDR_LOOPBACK);
	} else if (address->sa_family == AF_INET6) {
		return IN6_IS_ADDR_LOOPBACK(&((struct sockaddr_in6 *)(void *)address)->sin6_addr);
	}

	return (FALSE);
}