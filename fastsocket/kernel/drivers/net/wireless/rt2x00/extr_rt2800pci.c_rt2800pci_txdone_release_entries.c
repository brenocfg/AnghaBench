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
struct queue_entry {int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_STATUS_SET ; 
 int /*<<< orphan*/  rt2800_txdone_entry (struct queue_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800pci_get_txwi (struct queue_entry*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rt2800pci_txdone_release_entries(struct queue_entry *entry,
					     void *data)
{
	if (test_bit(ENTRY_DATA_STATUS_SET, &entry->flags)) {
		rt2800_txdone_entry(entry, entry->status,
				    rt2800pci_get_txwi(entry));
		return false;
	}

	/* No more frames to release */
	return true;
}