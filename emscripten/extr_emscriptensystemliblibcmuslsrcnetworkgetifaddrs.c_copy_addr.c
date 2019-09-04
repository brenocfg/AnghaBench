#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_family; } ;
struct TYPE_3__ {int sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
union sockany {struct sockaddr sa; TYPE_1__ v6; TYPE_2__ v4; } ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (void*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MC_LINKLOCAL (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void copy_addr(struct sockaddr **r, int af, union sockany *sa, void *addr, size_t addrlen, int ifindex)
{
	uint8_t *dst;
	int len;

	switch (af) {
	case AF_INET:
		dst = (uint8_t*) &sa->v4.sin_addr;
		len = 4;
		break;
	case AF_INET6:
		dst = (uint8_t*) &sa->v6.sin6_addr;
		len = 16;
		if (IN6_IS_ADDR_LINKLOCAL(addr) || IN6_IS_ADDR_MC_LINKLOCAL(addr))
			sa->v6.sin6_scope_id = ifindex;
		break;
	default:
		return;
	}
	if (addrlen < len) return;
	sa->sa.sa_family = af;
	memcpy(dst, addr, len);
	*r = &sa->sa;
}