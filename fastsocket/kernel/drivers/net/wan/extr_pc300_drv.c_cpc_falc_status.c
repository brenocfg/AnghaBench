#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  falc; } ;
typedef  TYPE_1__ pc300ch_t ;
struct TYPE_8__ {TYPE_1__* chan; } ;
typedef  TYPE_2__ pc300_t ;
struct TYPE_9__ {scalar_t__ prbs; scalar_t__ loss_mfa; scalar_t__ loss_fa; scalar_t__ yellow_alarm; scalar_t__ blue_alarm; scalar_t__ red_alarm; int /*<<< orphan*/  ebc; int /*<<< orphan*/  cec; int /*<<< orphan*/  cvc; int /*<<< orphan*/  fec; int /*<<< orphan*/  bec; int /*<<< orphan*/  rai; int /*<<< orphan*/  es; int /*<<< orphan*/  sec; int /*<<< orphan*/  ais; int /*<<< orphan*/  lmfa; int /*<<< orphan*/  farec; int /*<<< orphan*/  lfa; int /*<<< orphan*/  losr; int /*<<< orphan*/  los; int /*<<< orphan*/  pden; int /*<<< orphan*/  num_channels; scalar_t__ active; scalar_t__ sync; } ;
typedef  TYPE_3__ falc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_LOCK (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  CPC_UNLOCK (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void cpc_falc_status(pc300_t * card, int ch)
{
	pc300ch_t *chan = &card->chan[ch];
	falc_t *pfalc = (falc_t *) & chan->falc;
	unsigned long flags;

	CPC_LOCK(card, flags);
	printk("CH%d:   %s %s  %d channels\n",
	       ch, (pfalc->sync ? "SYNC" : ""), (pfalc->active ? "ACTIVE" : ""),
	       pfalc->num_channels);

	printk("        pden=%d,  los=%d,  losr=%d,  lfa=%d,  farec=%d\n",
	       pfalc->pden, pfalc->los, pfalc->losr, pfalc->lfa, pfalc->farec);
	printk("        lmfa=%d,  ais=%d,  sec=%d,  es=%d,  rai=%d\n",
	       pfalc->lmfa, pfalc->ais, pfalc->sec, pfalc->es, pfalc->rai);
	printk("        bec=%d,  fec=%d,  cvc=%d,  cec=%d,  ebc=%d\n",
	       pfalc->bec, pfalc->fec, pfalc->cvc, pfalc->cec, pfalc->ebc);

	printk("\n");
	printk("        STATUS: %s  %s  %s  %s  %s  %s\n",
	       (pfalc->red_alarm ? "RED" : ""),
	       (pfalc->blue_alarm ? "BLU" : ""),
	       (pfalc->yellow_alarm ? "YEL" : ""),
	       (pfalc->loss_fa ? "LFA" : ""),
	       (pfalc->loss_mfa ? "LMF" : ""), (pfalc->prbs ? "PRB" : ""));
	CPC_UNLOCK(card, flags);
}