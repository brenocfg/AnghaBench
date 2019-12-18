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
typedef  int /*<<< orphan*/  wcid_entry ;
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct mac_wcid_entry {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_WCID_ENTRY (int) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_multiread (struct rt2x00_dev*,int /*<<< orphan*/ ,struct mac_wcid_entry*,int) ; 

__attribute__((used)) static inline int rt2800_find_wcid(struct rt2x00_dev *rt2x00dev)
{
	struct mac_wcid_entry wcid_entry;
	int idx;
	u32 offset;

	/*
	 * Search for the first free WCID entry and return the corresponding
	 * index.
	 *
	 * Make sure the WCID starts _after_ the last possible shared key
	 * entry (>32).
	 *
	 * Since parts of the pairwise key table might be shared with
	 * the beacon frame buffers 6 & 7 we should only write into the
	 * first 222 entries.
	 */
	for (idx = 33; idx <= 222; idx++) {
		offset = MAC_WCID_ENTRY(idx);
		rt2800_register_multiread(rt2x00dev, offset, &wcid_entry,
					  sizeof(wcid_entry));
		if (is_broadcast_ether_addr(wcid_entry.mac))
			return idx;
	}

	/*
	 * Use -1 to indicate that we don't have any more space in the WCID
	 * table.
	 */
	return -1;
}