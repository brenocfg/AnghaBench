#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
union sctp_addr {TYPE_2__ v4; } ;
struct sk_buff {int dummy; } ;
struct sctphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void sctp_v4_from_skb(union sctp_addr *addr, struct sk_buff *skb,
			     int is_saddr)
{
	void *from;
	__be16 *port;
	struct sctphdr *sh;

	port = &addr->v4.sin_port;
	addr->v4.sin_family = AF_INET;

	sh = sctp_hdr(skb);
	if (is_saddr) {
		*port  = sh->source;
		from = &ip_hdr(skb)->saddr;
	} else {
		*port = sh->dest;
		from = &ip_hdr(skb)->daddr;
	}
	memcpy(&addr->v4.sin_addr.s_addr, from, sizeof(struct in_addr));
}