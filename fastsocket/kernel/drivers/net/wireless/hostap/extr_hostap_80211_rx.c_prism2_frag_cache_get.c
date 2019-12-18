#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct prism2_frag_entry {unsigned int seq; unsigned int last_frag; struct sk_buff* skb; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  first_frag_time; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  seq_ctrl; } ;
struct TYPE_6__ {size_t frag_next_idx; struct prism2_frag_entry* frag_cache; TYPE_1__* dev; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_5__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 size_t PRISM2_FRAG_CACHE_LEN ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct prism2_frag_entry* prism2_frag_cache_find (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
prism2_frag_cache_get(local_info_t *local, struct ieee80211_hdr *hdr)
{
	struct sk_buff *skb = NULL;
	u16 sc;
	unsigned int frag, seq;
	struct prism2_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctrl);
	frag = sc & IEEE80211_SCTL_FRAG;
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;

	if (frag == 0) {
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(local->dev->mtu +
				    sizeof(struct ieee80211_hdr) +
				    8 /* LLC */ +
				    2 /* alignment */ +
				    8 /* WEP */ + ETH_ALEN /* WDS */);
		if (skb == NULL)
			return NULL;

		entry = &local->frag_cache[local->frag_next_idx];
		local->frag_next_idx++;
		if (local->frag_next_idx >= PRISM2_FRAG_CACHE_LEN)
			local->frag_next_idx = 0;

		if (entry->skb != NULL)
			dev_kfree_skb(entry->skb);

		entry->first_frag_time = jiffies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		memcpy(entry->src_addr, hdr->addr2, ETH_ALEN);
		memcpy(entry->dst_addr, hdr->addr1, ETH_ALEN);
	} else {
		/* received a fragment of a frame for which the head fragment
		 * should have already been received */
		entry = prism2_frag_cache_find(local, seq, frag, hdr->addr2,
					       hdr->addr1);
		if (entry != NULL) {
			entry->last_frag = frag;
			skb = entry->skb;
		}
	}

	return skb;
}