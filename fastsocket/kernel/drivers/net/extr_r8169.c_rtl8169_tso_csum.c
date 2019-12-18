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
typedef  int u32 ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct TYPE_3__ {int tcp; int udp; } ;
struct rtl_tx_desc_info {int opts_offset; int mss_shift; TYPE_1__ checksum; } ;
struct rtl8169_private {int txd_version; } ;
struct iphdr {scalar_t__ protocol; } ;
struct TYPE_4__ {int gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int TD_LSO ; 
 int /*<<< orphan*/  TD_MSS_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 struct rtl_tx_desc_info* tx_desc_info ; 

__attribute__((used)) static inline void rtl8169_tso_csum(struct rtl8169_private *tp,
				    struct sk_buff *skb, u32 *opts)
{
	const struct rtl_tx_desc_info *info = tx_desc_info + tp->txd_version;
	u32 mss = skb_shinfo(skb)->gso_size;
	int offset = info->opts_offset;

	if (mss) {
		opts[0] |= TD_LSO;
		opts[offset] |= min(mss, TD_MSS_MAX) << info->mss_shift;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		const struct iphdr *ip = ip_hdr(skb);

		if (ip->protocol == IPPROTO_TCP)
			opts[offset] |= info->checksum.tcp;
		else if (ip->protocol == IPPROTO_UDP)
			opts[offset] |= info->checksum.udp;
		else
			WARN_ON_ONCE(1);
	}
}