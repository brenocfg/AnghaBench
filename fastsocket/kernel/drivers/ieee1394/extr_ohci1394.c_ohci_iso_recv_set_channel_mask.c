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
typedef  unsigned long long u64 ;
struct ohci_iso_recv {int /*<<< orphan*/  ohci; } ;
struct hpsb_iso {struct ohci_iso_recv* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskHiClear ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskHiSet ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskLoClear ; 
 int /*<<< orphan*/  OHCI1394_IRMultiChanMaskLoSet ; 
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ohci_iso_recv_set_channel_mask(struct hpsb_iso *iso, u64 mask)
{
	struct ohci_iso_recv *recv = iso->hostdata;
	int i;

	for (i = 0; i < 64; i++) {
		if (mask & (1ULL << i)) {
			if (i < 32)
				reg_write(recv->ohci, OHCI1394_IRMultiChanMaskLoSet, (1 << i));
			else
				reg_write(recv->ohci, OHCI1394_IRMultiChanMaskHiSet, (1 << (i-32)));
		} else {
			if (i < 32)
				reg_write(recv->ohci, OHCI1394_IRMultiChanMaskLoClear, (1 << i));
			else
				reg_write(recv->ohci, OHCI1394_IRMultiChanMaskHiClear, (1 << (i-32)));
		}
	}

	/* issue a dummy read to force all PCI writes to be posted immediately */
	mb();
	reg_read(recv->ohci, OHCI1394_IsochronousCycleTimer);
}