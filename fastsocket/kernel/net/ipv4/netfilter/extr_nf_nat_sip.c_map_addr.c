#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
union nf_inet_addr {scalar_t__ ip; } ;
struct sk_buff {int dummy; } ;
struct nf_conn {TYPE_10__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;
struct TYPE_17__ {scalar_t__ port; } ;
struct TYPE_18__ {TYPE_6__ udp; } ;
struct TYPE_16__ {scalar_t__ ip; } ;
struct TYPE_19__ {TYPE_7__ u; TYPE_5__ u3; } ;
struct TYPE_13__ {scalar_t__ port; } ;
struct TYPE_14__ {TYPE_2__ udp; } ;
struct TYPE_12__ {scalar_t__ ip; } ;
struct TYPE_15__ {TYPE_3__ u; TYPE_1__ u3; } ;
struct TYPE_20__ {TYPE_8__ src; TYPE_4__ dst; } ;
struct TYPE_11__ {TYPE_9__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int mangle_packet (struct sk_buff*,char const**,unsigned int*,unsigned int,unsigned int,char*,unsigned int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int ntohs (scalar_t__) ; 
 unsigned int sprintf (char*,char*,scalar_t__*,int) ; 

__attribute__((used)) static int map_addr(struct sk_buff *skb,
		    const char **dptr, unsigned int *datalen,
		    unsigned int matchoff, unsigned int matchlen,
		    union nf_inet_addr *addr, __be16 port)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	char buffer[sizeof("nnn.nnn.nnn.nnn:nnnnn")];
	unsigned int buflen;
	__be32 newaddr;
	__be16 newport;

	if (ct->tuplehash[dir].tuple.src.u3.ip == addr->ip &&
	    ct->tuplehash[dir].tuple.src.u.udp.port == port) {
		newaddr = ct->tuplehash[!dir].tuple.dst.u3.ip;
		newport = ct->tuplehash[!dir].tuple.dst.u.udp.port;
	} else if (ct->tuplehash[dir].tuple.dst.u3.ip == addr->ip &&
		   ct->tuplehash[dir].tuple.dst.u.udp.port == port) {
		newaddr = ct->tuplehash[!dir].tuple.src.u3.ip;
		newport = ct->tuplehash[!dir].tuple.src.u.udp.port;
	} else
		return 1;

	if (newaddr == addr->ip && newport == port)
		return 1;

	buflen = sprintf(buffer, "%pI4:%u", &newaddr, ntohs(newport));

	return mangle_packet(skb, dptr, datalen, matchoff, matchlen,
			     buffer, buflen);
}