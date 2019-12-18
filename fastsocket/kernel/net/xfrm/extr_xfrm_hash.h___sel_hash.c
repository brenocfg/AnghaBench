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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct xfrm_selector {int prefixlen_d; int prefixlen_s; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int __xfrm4_daddr_saddr_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int __xfrm6_daddr_saddr_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int __sel_hash(struct xfrm_selector *sel, unsigned short family, unsigned int hmask)
{
	xfrm_address_t *daddr = &sel->daddr;
	xfrm_address_t *saddr = &sel->saddr;
	unsigned int h = 0;

	switch (family) {
	case AF_INET:
		if (sel->prefixlen_d != 32 ||
		    sel->prefixlen_s != 32)
			return hmask + 1;

		h = __xfrm4_daddr_saddr_hash(daddr, saddr);
		break;

	case AF_INET6:
		if (sel->prefixlen_d != 128 ||
		    sel->prefixlen_s != 128)
			return hmask + 1;

		h = __xfrm6_daddr_saddr_hash(daddr, saddr);
		break;
	};
	h ^= (h >> 16);
	return h & hmask;
}