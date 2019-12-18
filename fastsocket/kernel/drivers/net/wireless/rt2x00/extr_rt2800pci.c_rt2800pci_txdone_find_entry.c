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
typedef  int /*<<< orphan*/  u32 ;
struct queue_entry {int /*<<< orphan*/  flags; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_STATUS_SET ; 
 scalar_t__ rt2800pci_txdone_entry_check (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rt2800pci_txdone_find_entry(struct queue_entry *entry, void *data)
{
	u32 status = *(u32 *)data;

	/*
	 * rt2800pci hardware might reorder frames when exchanging traffic
	 * with multiple BA enabled STAs.
	 *
	 * For example, a tx queue
	 *    [ STA1 | STA2 | STA1 | STA2 ]
	 * can result in tx status reports
	 *    [ STA1 | STA1 | STA2 | STA2 ]
	 * when the hw decides to aggregate the frames for STA1 into one AMPDU.
	 *
	 * To mitigate this effect, associate the tx status to the first frame
	 * in the tx queue with a matching wcid.
	 */
	if (rt2800pci_txdone_entry_check(entry, status) &&
	    !test_bit(ENTRY_DATA_STATUS_SET, &entry->flags)) {
		/*
		 * Got a matching frame, associate the tx status with
		 * the frame
		 */
		entry->status = status;
		set_bit(ENTRY_DATA_STATUS_SET, &entry->flags);
		return true;
	}

	/* Check the next frame */
	return false;
}