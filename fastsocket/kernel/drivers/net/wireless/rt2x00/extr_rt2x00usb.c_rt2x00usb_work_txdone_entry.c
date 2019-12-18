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
struct queue_entry {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 int /*<<< orphan*/  TXDONE_FAILURE ; 
 int /*<<< orphan*/  TXDONE_UNKNOWN ; 
 int /*<<< orphan*/  rt2x00lib_txdone_noinfo (struct queue_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00usb_work_txdone_entry(struct queue_entry *entry)
{
	/*
	 * If the transfer to hardware succeeded, it does not mean the
	 * frame was send out correctly. It only means the frame
	 * was successfully pushed to the hardware, we have no
	 * way to determine the transmission status right now.
	 * (Only indirectly by looking at the failed TX counters
	 * in the register).
	 */
	if (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		rt2x00lib_txdone_noinfo(entry, TXDONE_FAILURE);
	else
		rt2x00lib_txdone_noinfo(entry, TXDONE_UNKNOWN);
}