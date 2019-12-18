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
typedef  int /*<<< orphan*/  u16 ;
struct libipw_hdr_4addr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  seq_ctl; } ;
struct libipw_frag_entry {int /*<<< orphan*/ * skb; } ;
struct libipw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBIPW_DEBUG_FRAG (char*,unsigned int) ; 
 unsigned int WLAN_GET_SEQ_SEQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct libipw_frag_entry* libipw_frag_cache_find (struct libipw_device*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libipw_frag_cache_invalidate(struct libipw_device *ieee,
					   struct libipw_hdr_4addr *hdr)
{
	u16 sc;
	unsigned int seq;
	struct libipw_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctl);
	seq = WLAN_GET_SEQ_SEQ(sc);

	entry = libipw_frag_cache_find(ieee, seq, -1, hdr->addr2,
					  hdr->addr1);

	if (entry == NULL) {
		LIBIPW_DEBUG_FRAG("could not invalidate fragment cache "
				     "entry (seq=%u)\n", seq);
		return -1;
	}

	entry->skb = NULL;
	return 0;
}