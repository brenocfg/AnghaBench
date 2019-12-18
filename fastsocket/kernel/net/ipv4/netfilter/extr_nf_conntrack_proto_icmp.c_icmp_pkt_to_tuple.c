#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {TYPE_6__ icmp; } ;
struct TYPE_15__ {TYPE_8__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ icmp; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_7__ dst; TYPE_3__ src; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_4__ echo; } ;
struct icmphdr {int /*<<< orphan*/  code; TYPE_5__ un; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  _hdr ;

/* Variables and functions */
 struct icmphdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct icmphdr*) ; 

__attribute__((used)) static bool icmp_pkt_to_tuple(const struct sk_buff *skb, unsigned int dataoff,
			      struct nf_conntrack_tuple *tuple)
{
	const struct icmphdr *hp;
	struct icmphdr _hdr;

	hp = skb_header_pointer(skb, dataoff, sizeof(_hdr), &_hdr);
	if (hp == NULL)
		return false;

	tuple->dst.u.icmp.type = hp->type;
	tuple->src.u.icmp.id = hp->un.echo.id;
	tuple->dst.u.icmp.code = hp->code;

	return true;
}