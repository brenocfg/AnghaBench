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
struct fritz_bcs {scalar_t__ rcvidx; unsigned char* rcvbuf; scalar_t__ channel; struct fritz_adapter* adapter; } ;
struct fritz_adapter {int type; int /*<<< orphan*/  hw_lock; scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ AVM_DATA ; 
#define  AVM_FRITZ_PCI 130 
#define  AVM_FRITZ_PCIV2 129 
#define  AVM_FRITZ_PNP 128 
 scalar_t__ AVM_HDLC_FIFO_1 ; 
 scalar_t__ AVM_HDLC_FIFO_2 ; 
 unsigned char AVM_IDX_HDLC_1 ; 
 unsigned char AVM_IDX_HDLC_2 ; 
 scalar_t__ AVM_INDEX ; 
 int /*<<< orphan*/  DBG (int,char*,...) ; 
 scalar_t__ HDLC_FIFO ; 
 scalar_t__ HSCX_BUFMAX ; 
 int /*<<< orphan*/  insb (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  insl (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hdlc_empty_fifo(struct fritz_bcs *bcs, int count)
{
	struct fritz_adapter *adapter = bcs->adapter;
	unsigned char *p;
	unsigned char idx = bcs->channel ? AVM_IDX_HDLC_2 : AVM_IDX_HDLC_1;

	DBG(0x10, "hdlc_empty_fifo %d", count);
	if (bcs->rcvidx + count > HSCX_BUFMAX) {
		DBG(0x10, "hdlc_empty_fifo: incoming packet too large");
		return;
	}
	p = bcs->rcvbuf + bcs->rcvidx;
	bcs->rcvidx += count;
	switch (adapter->type) {
	case AVM_FRITZ_PCI:
		spin_lock(&adapter->hw_lock);
		outl(idx, adapter->io + AVM_INDEX);
		insl(adapter->io + AVM_DATA + HDLC_FIFO, 
		     p, (count + 3) / 4);
		spin_unlock(&adapter->hw_lock);
		break;
	case AVM_FRITZ_PCIV2:
		insl(adapter->io + 
		     (bcs->channel ? AVM_HDLC_FIFO_2 : AVM_HDLC_FIFO_1),
		     p, (count + 3) / 4);
		break;
	case AVM_FRITZ_PNP:
		spin_lock(&adapter->hw_lock);
		outb(idx, adapter->io + AVM_INDEX);
		insb(adapter->io + AVM_DATA, p, count);
		spin_unlock(&adapter->hw_lock);
		break;
	}
}