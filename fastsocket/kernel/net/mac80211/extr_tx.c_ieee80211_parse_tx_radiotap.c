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
typedef  int u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_radiotap_iterator {int this_arg_index; int* this_arg; scalar_t__ _max_length; } ;
struct ieee80211_radiotap_header {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ FCS_LEN ; 
#define  IEEE80211_RADIOTAP_FLAGS 129 
 int IEEE80211_RADIOTAP_F_FCS ; 
 int IEEE80211_RADIOTAP_F_FRAG ; 
 int IEEE80211_RADIOTAP_F_TX_NOACK ; 
 int IEEE80211_RADIOTAP_F_WEP ; 
#define  IEEE80211_RADIOTAP_TX_FLAGS 128 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_DONTFRAG ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_INTFL_DONT_ENCRYPT ; 
 int get_unaligned_le16 (int*) ; 
 int ieee80211_radiotap_iterator_init (struct ieee80211_radiotap_iterator*,struct ieee80211_radiotap_header*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ieee80211_radiotap_iterator_next (struct ieee80211_radiotap_iterator*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static bool ieee80211_parse_tx_radiotap(struct sk_buff *skb)
{
	struct ieee80211_radiotap_iterator iterator;
	struct ieee80211_radiotap_header *rthdr =
		(struct ieee80211_radiotap_header *) skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int ret = ieee80211_radiotap_iterator_init(&iterator, rthdr, skb->len,
						   NULL);
	u16 txflags;

	info->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
		       IEEE80211_TX_CTL_DONTFRAG;

	/*
	 * for every radiotap entry that is present
	 * (ieee80211_radiotap_iterator_next returns -ENOENT when no more
	 * entries present, or -EINVAL on error)
	 */

	while (!ret) {
		ret = ieee80211_radiotap_iterator_next(&iterator);

		if (ret)
			continue;

		/* see if this argument is something we can use */
		switch (iterator.this_arg_index) {
		/*
		 * You must take care when dereferencing iterator.this_arg
		 * for multibyte types... the pointer is not aligned.  Use
		 * get_unaligned((type *)iterator.this_arg) to dereference
		 * iterator.this_arg for type "type" safely on all arches.
		*/
		case IEEE80211_RADIOTAP_FLAGS:
			if (*iterator.this_arg & IEEE80211_RADIOTAP_F_FCS) {
				/*
				 * this indicates that the skb we have been
				 * handed has the 32-bit FCS CRC at the end...
				 * we should react to that by snipping it off
				 * because it will be recomputed and added
				 * on transmission
				 */
				if (skb->len < (iterator._max_length + FCS_LEN))
					return false;

				skb_trim(skb, skb->len - FCS_LEN);
			}
			if (*iterator.this_arg & IEEE80211_RADIOTAP_F_WEP)
				info->flags &= ~IEEE80211_TX_INTFL_DONT_ENCRYPT;
			if (*iterator.this_arg & IEEE80211_RADIOTAP_F_FRAG)
				info->flags &= ~IEEE80211_TX_CTL_DONTFRAG;
			break;

		case IEEE80211_RADIOTAP_TX_FLAGS:
			txflags = get_unaligned_le16(iterator.this_arg);
			if (txflags & IEEE80211_RADIOTAP_F_TX_NOACK)
				info->flags |= IEEE80211_TX_CTL_NO_ACK;
			break;

		/*
		 * Please update the file
		 * Documentation/networking/mac80211-injection.txt
		 * when parsing new fields here.
		 */

		default:
			break;
		}
	}

	if (ret != -ENOENT) /* ie, if we didn't simply run out of fields */
		return false;

	/*
	 * remove the radiotap header
	 * iterator->_max_length was sanity-checked against
	 * skb->len by iterator init
	 */
	skb_pull(skb, iterator._max_length);

	return true;
}