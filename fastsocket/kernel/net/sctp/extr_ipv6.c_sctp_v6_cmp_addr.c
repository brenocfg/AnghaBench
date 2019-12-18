#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__* s6_addr32; } ;
struct TYPE_12__ {scalar_t__ sin6_port; scalar_t__ sin6_scope_id; TYPE_5__ sin6_addr; } ;
struct TYPE_10__ {scalar_t__ s_addr; } ;
struct TYPE_11__ {scalar_t__ sin_port; TYPE_2__ sin_addr; } ;
struct TYPE_9__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_4__ v6; TYPE_3__ v4; TYPE_1__ sa; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int /*<<< orphan*/  ipv6_addr_equal (TYPE_5__*,TYPE_5__*) ; 
 int ipv6_addr_type (TYPE_5__*) ; 
 scalar_t__ ipv6_addr_v4mapped (TYPE_5__*) ; 

__attribute__((used)) static int sctp_v6_cmp_addr(const union sctp_addr *addr1,
			    const union sctp_addr *addr2)
{
	if (addr1->sa.sa_family != addr2->sa.sa_family) {
		if (addr1->sa.sa_family == AF_INET &&
		    addr2->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr2->v6.sin6_addr)) {
			if (addr2->v6.sin6_port == addr1->v4.sin_port &&
			    addr2->v6.sin6_addr.s6_addr32[3] ==
			    addr1->v4.sin_addr.s_addr)
				return 1;
		}
		if (addr2->sa.sa_family == AF_INET &&
		    addr1->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr1->v6.sin6_addr)) {
			if (addr1->v6.sin6_port == addr2->v4.sin_port &&
			    addr1->v6.sin6_addr.s6_addr32[3] ==
			    addr2->v4.sin_addr.s_addr)
				return 1;
		}
		return 0;
	}
	if (!ipv6_addr_equal(&addr1->v6.sin6_addr, &addr2->v6.sin6_addr))
		return 0;
	/* If this is a linklocal address, compare the scope_id. */
	if (ipv6_addr_type(&addr1->v6.sin6_addr) & IPV6_ADDR_LINKLOCAL) {
		if (addr1->v6.sin6_scope_id && addr2->v6.sin6_scope_id &&
		    (addr1->v6.sin6_scope_id != addr2->v6.sin6_scope_id)) {
			return 0;
		}
	}

	return 1;
}