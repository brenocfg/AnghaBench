#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  host_no; scalar_t__ hostdata; } ;
typedef  long off_t ;
struct TYPE_4__ {TYPE_2__* icmb; TYPE_2__* ogmb; } ;
struct TYPE_6__ {int bus_on; int bus_off; int /*<<< orphan*/  next_ogmb; int /*<<< orphan*/  control; TYPE_1__ mb; int /*<<< orphan*/  int_counter; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; int /*<<< orphan*/  rev2; int /*<<< orphan*/  rev1; } ;
struct TYPE_5__ {scalar_t__ status; } ;
typedef  TYPE_2__ Mailbox ;
typedef  TYPE_3__ Adapter ;

/* Variables and functions */
 size_t ICMB_CNT ; 
 size_t OGMB_CNT ; 
 int /*<<< orphan*/  SPRINTF (char*,...) ; 
 size_t i ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int wd7000_set_info (char*,int,struct Scsi_Host*) ; 

__attribute__((used)) static int wd7000_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset, int length,  int inout)
{
	Adapter *adapter = (Adapter *)host->hostdata;
	unsigned long flags;
	char *pos = buffer;
#ifdef WD7000_DEBUG
	Mailbox *ogmbs, *icmbs;
	short count;
#endif

	/*
	 * Has data been written to the file ?
	 */
	if (inout)
		return (wd7000_set_info(buffer, length, host));

	spin_lock_irqsave(host->host_lock, flags);
	SPRINTF("Host scsi%d: Western Digital WD-7000 (rev %d.%d)\n", host->host_no, adapter->rev1, adapter->rev2);
	SPRINTF("  IO base:      0x%x\n", adapter->iobase);
	SPRINTF("  IRQ:          %d\n", adapter->irq);
	SPRINTF("  DMA channel:  %d\n", adapter->dma);
	SPRINTF("  Interrupts:   %d\n", adapter->int_counter);
	SPRINTF("  BUS_ON time:  %d nanoseconds\n", adapter->bus_on * 125);
	SPRINTF("  BUS_OFF time: %d nanoseconds\n", adapter->bus_off * 125);

#ifdef WD7000_DEBUG
	ogmbs = adapter->mb.ogmb;
	icmbs = adapter->mb.icmb;

	SPRINTF("\nControl port value: 0x%x\n", adapter->control);
	SPRINTF("Incoming mailbox:\n");
	SPRINTF("  size: %d\n", ICMB_CNT);
	SPRINTF("  queued messages: ");

	for (i = count = 0; i < ICMB_CNT; i++)
		if (icmbs[i].status) {
			count++;
			SPRINTF("0x%x ", i);
		}

	SPRINTF(count ? "\n" : "none\n");

	SPRINTF("Outgoing mailbox:\n");
	SPRINTF("  size: %d\n", OGMB_CNT);
	SPRINTF("  next message: 0x%x\n", adapter->next_ogmb);
	SPRINTF("  queued messages: ");

	for (i = count = 0; i < OGMB_CNT; i++)
		if (ogmbs[i].status) {
			count++;
			SPRINTF("0x%x ", i);
		}

	SPRINTF(count ? "\n" : "none\n");
#endif

	spin_unlock_irqrestore(host->host_lock, flags);

	/*
	 * Calculate start of next buffer, and return value.
	 */
	*start = buffer + offset;

	if ((pos - buffer) < offset)
		return (0);
	else if ((pos - buffer - offset) < length)
		return (pos - buffer - offset);
	else
		return (length);
}