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
struct TYPE_3__ {unsigned char mode; unsigned char xml; unsigned char cmd; } ;
struct TYPE_4__ {TYPE_1__ sr; int /*<<< orphan*/  ctrl; } ;
struct fritz_bcs {TYPE_2__ ctrl; scalar_t__ channel; struct fritz_adapter* adapter; } ;
struct fritz_adapter {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ AVM_DATA ; 
 unsigned char AVM_IDX_HDLC_1 ; 
 unsigned char AVM_IDX_HDLC_2 ; 
 scalar_t__ AVM_INDEX ; 
 int /*<<< orphan*/  DBG (int,char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HDLC_STATUS ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void __fcpnp_write_ctrl(struct fritz_bcs *bcs, int which)
{
	struct fritz_adapter *adapter = bcs->adapter;
	unsigned char idx = bcs->channel ? AVM_IDX_HDLC_2 : AVM_IDX_HDLC_1;

	DBG(0x40, "hdlc %c wr%x ctrl %x",
	    'A' + bcs->channel, which, bcs->ctrl.ctrl);

	outb(idx, adapter->io + AVM_INDEX);
	if (which & 4)
		outb(bcs->ctrl.sr.mode, 
		     adapter->io + AVM_DATA + HDLC_STATUS + 2);
	if (which & 2)
		outb(bcs->ctrl.sr.xml, 
		     adapter->io + AVM_DATA + HDLC_STATUS + 1);
	if (which & 1)
		outb(bcs->ctrl.sr.cmd,
		     adapter->io + AVM_DATA + HDLC_STATUS + 0);
}