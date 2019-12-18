#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sctphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; } ;
struct TYPE_11__ {TYPE_4__ sctp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {TYPE_1__ sctp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;

/* Variables and functions */
 struct sctphdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct sctphdr*) ; 

__attribute__((used)) static bool sctp_pkt_to_tuple(const struct sk_buff *skb, unsigned int dataoff,
			      struct nf_conntrack_tuple *tuple)
{
	const struct sctphdr *hp;
	struct sctphdr _hdr;

	/* Actually only need first 8 bytes. */
	hp = skb_header_pointer(skb, dataoff, 8, &_hdr);
	if (hp == NULL)
		return false;

	tuple->src.u.sctp.port = hp->source;
	tuple->dst.u.sctp.port = hp->dest;
	return true;
}