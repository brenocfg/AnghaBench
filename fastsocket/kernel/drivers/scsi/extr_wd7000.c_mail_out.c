#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int unchar ;
struct TYPE_8__ {TYPE_3__* ogmb; } ;
struct TYPE_11__ {int next_ogmb; TYPE_2__* sh; TYPE_1__ mb; } ;
struct TYPE_10__ {int status; scalar_t__ scbptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  Scb ;
typedef  TYPE_3__ Mailbox ;
typedef  TYPE_4__ Adapter ;

/* Variables and functions */
 int OGMB_CNT ; 
 int START_OGMB ; 
 int /*<<< orphan*/  any2scsi (int*,int) ; 
 int /*<<< orphan*/  command_out (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wd7000_enable_intr (TYPE_4__*) ; 

__attribute__((used)) static int mail_out(Adapter * host, Scb * scbptr)
/*
 *  Note: this can also be used for ICBs; just cast to the parm type.
 */
{
	int i, ogmb;
	unsigned long flags;
	unchar start_ogmb;
	Mailbox *ogmbs = host->mb.ogmb;
	int *next_ogmb = &(host->next_ogmb);

	dprintk("wd7000_mail_out: 0x%06lx", (long) scbptr);

	/* We first look for a free outgoing mailbox */
	spin_lock_irqsave(host->sh->host_lock, flags);
	ogmb = *next_ogmb;
	for (i = 0; i < OGMB_CNT; i++) {
		if (ogmbs[ogmb].status == 0) {
			dprintk(" using OGMB 0x%x", ogmb);
			ogmbs[ogmb].status = 1;
			any2scsi((unchar *) ogmbs[ogmb].scbptr, (int) scbptr);

			*next_ogmb = (ogmb + 1) % OGMB_CNT;
			break;
		} else
			ogmb = (ogmb + 1) % OGMB_CNT;
	}
	spin_unlock_irqrestore(host->sh->host_lock, flags);

	dprintk(", scb is 0x%06lx", (long) scbptr);

	if (i >= OGMB_CNT) {
		/*
		 *  Alternatively, we might issue the "interrupt on free OGMB",
		 *  and sleep, but it must be ensured that it isn't the init
		 *  task running.  Instead, this version assumes that the caller
		 *  will be persistent, and try again.  Since it's the adapter
		 *  that marks OGMB's free, waiting even with interrupts off
		 *  should work, since they are freed very quickly in most cases.
		 */
		dprintk(", no free OGMBs.\n");
		return (0);
	}

	wd7000_enable_intr(host);

	start_ogmb = START_OGMB | ogmb;
	command_out(host, &start_ogmb, 1);

	dprintk(", awaiting interrupt.\n");

	return (1);
}