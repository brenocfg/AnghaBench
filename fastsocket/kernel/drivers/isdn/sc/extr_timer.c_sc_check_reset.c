#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t shmem_pgport; int shmem_magic; int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  devicename; scalar_t__ StartOnReset; scalar_t__ rambase; int /*<<< orphan*/ * ioport; } ;

/* Variables and functions */
 scalar_t__ CHECKRESET_TIME ; 
 unsigned long SIGNATURE ; 
 scalar_t__ SIG_OFFSET ; 
 int /*<<< orphan*/  flushreadfifo (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__** sc_adapter ; 
 int /*<<< orphan*/  setup_ports (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  startproc (int) ; 

void sc_check_reset(unsigned long data)
{
	unsigned long flags;
	unsigned long sig;
	int card = (unsigned int) data;

	pr_debug("%s: check_timer timer called\n",
		sc_adapter[card]->devicename);

	/* Setup the io ports */
	setup_ports(card);

	spin_lock_irqsave(&sc_adapter[card]->lock, flags);
	outb(sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport],
		(sc_adapter[card]->shmem_magic>>14) | 0x80);
	sig = (unsigned long) *((unsigned long *)(sc_adapter[card]->rambase + SIG_OFFSET));

	/* check the signature */
	if(sig == SIGNATURE) {
		flushreadfifo(card);
		spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
		/* See if we need to do a startproc */
		if (sc_adapter[card]->StartOnReset)
			startproc(card);
	} else  {
		pr_debug("%s: No signature yet, waiting another %lu jiffies.\n",
			sc_adapter[card]->devicename, CHECKRESET_TIME);
		mod_timer(&sc_adapter[card]->reset_timer, jiffies+CHECKRESET_TIME);
		spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
	}
}