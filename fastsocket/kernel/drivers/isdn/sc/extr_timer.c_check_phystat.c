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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  stat_timer; scalar_t__ nphystat; scalar_t__ phystat; int /*<<< orphan*/  devicename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPID ; 
 scalar_t__ CHECKSTAT_TIME ; 
 int /*<<< orphan*/  ISDN_STAT_RUN ; 
 int /*<<< orphan*/  ISDN_STAT_STOP ; 
 int /*<<< orphan*/  ceReqClass2 ; 
 int /*<<< orphan*/  ceReqPhyStatus ; 
 int /*<<< orphan*/  ceReqTypePhy ; 
 int /*<<< orphan*/  indicate_status (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__** sc_adapter ; 
 int /*<<< orphan*/  sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void check_phystat(unsigned long data)
{
	unsigned long flags;
	int card = (unsigned int) data;

	pr_debug("%s: Checking status...\n", sc_adapter[card]->devicename);
	/* 
	 * check the results of the last PhyStat and change only if
	 * has changed drastically
	 */
	if (sc_adapter[card]->nphystat && !sc_adapter[card]->phystat) {   /* All is well */
		pr_debug("PhyStat transition to RUN\n");
		pr_info("%s: Switch contacted, transmitter enabled\n", 
			sc_adapter[card]->devicename);
		indicate_status(card, ISDN_STAT_RUN, 0, NULL);
	}
	else if (!sc_adapter[card]->nphystat && sc_adapter[card]->phystat) {   /* All is not well */
		pr_debug("PhyStat transition to STOP\n");
		pr_info("%s: Switch connection lost, transmitter disabled\n", 
			sc_adapter[card]->devicename);

		indicate_status(card, ISDN_STAT_STOP, 0, NULL);
	}

	sc_adapter[card]->phystat = sc_adapter[card]->nphystat;

	/* Reinitialize the timer */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);
	mod_timer(&sc_adapter[card]->stat_timer, jiffies+CHECKSTAT_TIME);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);

	/* Send a new cePhyStatus message */
	sendmessage(card, CEPID,ceReqTypePhy,ceReqClass2,
		ceReqPhyStatus,0,0,NULL);
}