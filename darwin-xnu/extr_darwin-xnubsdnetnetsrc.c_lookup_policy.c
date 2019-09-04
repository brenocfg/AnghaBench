#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int sin6_len; TYPE_4__ sin6_addr; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
union sockaddr_in_4_6 {TYPE_2__ sin; struct sockaddr_in6 sin6; TYPE_3__ sa; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in6_addrpolicy {int dummy; } ;
typedef  int /*<<< orphan*/  mapped ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 TYPE_4__ IN6ADDR_V4MAPPED_INIT ; 
 struct in6_addrpolicy* in6_addrsel_lookup_policy (struct sockaddr_in6*) ; 

__attribute__((used)) static struct in6_addrpolicy *
lookup_policy(struct sockaddr* sa)
{
	// alignment fun - if sa_family is AF_INET or AF_INET6, this is one of those
	// addresses and it should be aligned, so this should be safe.
	union sockaddr_in_4_6 *addr = (union sockaddr_in_4_6 *)(void*)sa;
	if (addr->sa.sa_family == AF_INET6) {
		return in6_addrsel_lookup_policy(&addr->sin6);
	} else if (sa->sa_family == AF_INET) {
		struct sockaddr_in6 mapped = {
			.sin6_family = AF_INET6,
			.sin6_len = sizeof(mapped),
			.sin6_addr = IN6ADDR_V4MAPPED_INIT,
		};
		mapped.sin6_addr.s6_addr32[3] = addr->sin.sin_addr.s_addr;
		return in6_addrsel_lookup_policy(&mapped);
	}
	return NULL;
}