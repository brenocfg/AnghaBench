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
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; } ;
union necp_sockaddr_union {TYPE_4__ sin6; TYPE_3__ sa; TYPE_2__ sin; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_ANY ; 

__attribute__((used)) static inline bool
necp_address_is_wildcard(const union necp_sockaddr_union * const addr)
{
	return ((addr->sa.sa_family == AF_INET && addr->sin.sin_addr.s_addr == INADDR_ANY) ||
			(addr->sa.sa_family == AF_INET6 && IN6_IS_ADDR_UNSPECIFIED(&addr->sin6.sin6_addr)));
}