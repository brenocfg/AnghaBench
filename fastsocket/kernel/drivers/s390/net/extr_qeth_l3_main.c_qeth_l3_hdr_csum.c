#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int ext_flags; } ;
struct TYPE_8__ {TYPE_3__ l3; } ;
struct qeth_hdr {TYPE_4__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_csum; } ;
struct TYPE_5__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_2__ perf_stats; TYPE_1__ options; } ;
struct iphdr {scalar_t__ protocol; scalar_t__ check; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int QETH_HDR_EXT_CSUM_HDR_REQ ; 
 int QETH_HDR_EXT_CSUM_TRANSP_REQ ; 
 int QETH_HDR_EXT_UDP ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void qeth_l3_hdr_csum(struct qeth_card *card,
		struct qeth_hdr *hdr, struct sk_buff *skb)
{
	struct iphdr *iph = ip_hdr(skb);

	/* tcph->check contains already the pseudo hdr checksum
	 * so just set the header flags
	 */
	if (iph->protocol == IPPROTO_UDP)
		hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_UDP;
	hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_CSUM_TRANSP_REQ |
		QETH_HDR_EXT_CSUM_HDR_REQ;
	iph->check = 0;
	if (card->options.performance_stats)
		card->perf_stats.tx_csum++;
}