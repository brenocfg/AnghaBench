#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_conn {int dummy; } ;
typedef  union nf_inet_addr __be16 ;
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int choice; TYPE_1__ ip6Address; TYPE_2__ ipAddress; } ;
typedef  TYPE_3__ TransportAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  eTransportAddress_ip6Address 129 
#define  eTransportAddress_ipAddress 128 
 int /*<<< orphan*/  memcpy (union nf_inet_addr*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 

int get_h225_addr(struct nf_conn *ct, unsigned char *data,
		  TransportAddress *taddr,
		  union nf_inet_addr *addr, __be16 *port)
{
	const unsigned char *p;
	int len;

	switch (taddr->choice) {
	case eTransportAddress_ipAddress:
		if (nf_ct_l3num(ct) != AF_INET)
			return 0;
		p = data + taddr->ipAddress.ip;
		len = 4;
		break;
	case eTransportAddress_ip6Address:
		if (nf_ct_l3num(ct) != AF_INET6)
			return 0;
		p = data + taddr->ip6Address.ip;
		len = 16;
		break;
	default:
		return 0;
	}

	memcpy(addr, p, len);
	memset((void *)addr + len, 0, sizeof(*addr) - len);
	memcpy(port, p + len, sizeof(__be16));

	return 1;
}