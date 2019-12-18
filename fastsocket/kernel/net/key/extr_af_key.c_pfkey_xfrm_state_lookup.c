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
typedef  scalar_t__ uint16_t ;
struct xfrm_state {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {unsigned short sa_family; } ;
struct sadb_sa {int /*<<< orphan*/  sadb_sa_spi; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_satype; } ;
struct sadb_address {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  DUMMY_MARK ; 
 int SADB_EXT_ADDRESS_DST ; 
 int SADB_EXT_SA ; 
 scalar_t__ pfkey_satype2proto (int /*<<< orphan*/ ) ; 
 struct xfrm_state* xfrm_state_lookup_with_mark (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned short) ; 

__attribute__((used)) static struct  xfrm_state *pfkey_xfrm_state_lookup(struct net *net, struct sadb_msg *hdr, void **ext_hdrs)
{
	struct sadb_sa *sa;
	struct sadb_address *addr;
	uint16_t proto;
	unsigned short family;
	xfrm_address_t *xaddr;

	sa = (struct sadb_sa *) ext_hdrs[SADB_EXT_SA-1];
	if (sa == NULL)
		return NULL;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	if (proto == 0)
		return NULL;

	/* sadb_address_len should be checked by caller */
	addr = (struct sadb_address *) ext_hdrs[SADB_EXT_ADDRESS_DST-1];
	if (addr == NULL)
		return NULL;

	family = ((struct sockaddr *)(addr + 1))->sa_family;
	switch (family) {
	case AF_INET:
		xaddr = (xfrm_address_t *)&((struct sockaddr_in *)(addr + 1))->sin_addr;
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		xaddr = (xfrm_address_t *)&((struct sockaddr_in6 *)(addr + 1))->sin6_addr;
		break;
#endif
	default:
		xaddr = NULL;
	}

	if (!xaddr)
		return NULL;

	return xfrm_state_lookup_with_mark(net, DUMMY_MARK, xaddr, sa->sadb_sa_spi, proto, family);
}