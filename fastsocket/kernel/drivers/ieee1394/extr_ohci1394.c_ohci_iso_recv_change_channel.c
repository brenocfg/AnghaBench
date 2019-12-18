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
struct ohci_iso_recv {int /*<<< orphan*/  ohci; } ;
struct hpsb_iso {struct ohci_iso_recv* hostdata; } ;

/* Variables and functions */
 int OHCI1394_IRMultiChanMaskHiClear ; 
 int OHCI1394_IRMultiChanMaskHiSet ; 
 int OHCI1394_IRMultiChanMaskLoClear ; 
 int OHCI1394_IRMultiChanMaskLoSet ; 
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ohci_iso_recv_change_channel(struct hpsb_iso *iso, unsigned char channel, int listen)
{
	struct ohci_iso_recv *recv = iso->hostdata;
	int reg, i;

	if (channel < 32) {
		reg = listen ? OHCI1394_IRMultiChanMaskLoSet : OHCI1394_IRMultiChanMaskLoClear;
		i = channel;
	} else {
		reg = listen ? OHCI1394_IRMultiChanMaskHiSet : OHCI1394_IRMultiChanMaskHiClear;
		i = channel - 32;
	}

	reg_write(recv->ohci, reg, (1 << i));

	/* issue a dummy read to force all PCI writes to be posted immediately */
	mb();
	reg_read(recv->ohci, OHCI1394_IsochronousCycleTimer);
}