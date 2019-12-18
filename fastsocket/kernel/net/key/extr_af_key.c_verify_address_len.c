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
typedef  int /*<<< orphan*/  uint64_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct sadb_address {int sadb_address_len; int sadb_address_prefixlen; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 

__attribute__((used)) static int verify_address_len(void *p)
{
	struct sadb_address *sp = p;
	struct sockaddr *addr = (struct sockaddr *)(sp + 1);
	struct sockaddr_in *sin;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	struct sockaddr_in6 *sin6;
#endif
	int len;

	switch (addr->sa_family) {
	case AF_INET:
		len = DIV_ROUND_UP(sizeof(*sp) + sizeof(*sin), sizeof(uint64_t));
		if (sp->sadb_address_len != len ||
		    sp->sadb_address_prefixlen > 32)
			return -EINVAL;
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		len = DIV_ROUND_UP(sizeof(*sp) + sizeof(*sin6), sizeof(uint64_t));
		if (sp->sadb_address_len != len ||
		    sp->sadb_address_prefixlen > 128)
			return -EINVAL;
		break;
#endif
	default:
		/* It is user using kernel to keep track of security
		 * associations for another protocol, such as
		 * OSPF/RSVP/RIPV2/MIP.  It is user's job to verify
		 * lengths.
		 *
		 * XXX Actually, association/policy database is not yet
		 * XXX able to cope with arbitrary sockaddr families.
		 * XXX When it can, remove this -EINVAL.  -DaveM
		 */
		return -EINVAL;
		break;
	}

	return 0;
}