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
typedef  scalar_t__ u_int ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sadb_address {scalar_t__ sadb_address_proto; scalar_t__ sadb_address_prefixlen; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {int sa_family; scalar_t__ sa_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  out_invaddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 TYPE_2__* PFKEY_ADDR_SADDR (struct sadb_address*) ; 
 int /*<<< orphan*/  PFKEY_STAT_INCREMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 TYPE_1__ pfkeystat ; 

__attribute__((used)) static int
key_validate_address_pair(struct sadb_address *src0,
						  struct sadb_address *dst0)
{
	u_int plen = 0;

	/* check upper layer protocol */
	if (src0->sadb_address_proto != dst0->sadb_address_proto) {
		ipseclog((LOG_DEBUG, "key_parse: upper layer protocol mismatched.\n"));
		PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
		return (EINVAL);
	}

	/* check family */
	if (PFKEY_ADDR_SADDR(src0)->sa_family !=
		PFKEY_ADDR_SADDR(dst0)->sa_family) {
		ipseclog((LOG_DEBUG, "key_parse: address family mismatched.\n"));
		PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
		return (EINVAL);
	}
	if (PFKEY_ADDR_SADDR(src0)->sa_len !=
		PFKEY_ADDR_SADDR(dst0)->sa_len) {
		ipseclog((LOG_DEBUG,
				  "key_parse: address struct size mismatched.\n"));
		PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
		return (EINVAL);
	}

	switch (PFKEY_ADDR_SADDR(src0)->sa_family) {
		case AF_INET:
			if (PFKEY_ADDR_SADDR(src0)->sa_len != sizeof(struct sockaddr_in)) {
				PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
				return (EINVAL);
			}
			break;
		case AF_INET6:
			if (PFKEY_ADDR_SADDR(src0)->sa_len != sizeof(struct sockaddr_in6)) {
				PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
				return (EINVAL);
			}
			break;
		default:
			ipseclog((LOG_DEBUG,
					  "key_parse: unsupported address family.\n"));
			PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
			return (EAFNOSUPPORT);
	}

	switch (PFKEY_ADDR_SADDR(src0)->sa_family) {
		case AF_INET:
			plen = sizeof(struct in_addr) << 3;
			break;
		case AF_INET6:
			plen = sizeof(struct in6_addr) << 3;
			break;
		default:
			plen = 0;	/*fool gcc*/
			break;
	}

	/* check max prefix length */
	if (src0->sadb_address_prefixlen > plen ||
		dst0->sadb_address_prefixlen > plen) {
		ipseclog((LOG_DEBUG,
				  "key_parse: illegal prefixlen.\n"));
		PFKEY_STAT_INCREMENT(pfkeystat.out_invaddr);
		return (EINVAL);
	}

	/*
	 * prefixlen == 0 is valid because there can be a case when
	 * all addresses are matched.
	 */
	return (0);
}