#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* dev; scalar_t__ chan; } ;
typedef  TYPE_3__ pc300dev_t ;
struct TYPE_12__ {int channel; scalar_t__ card; } ;
typedef  TYPE_4__ pc300ch_t ;
struct TYPE_10__ {scalar_t__ scabase; } ;
struct TYPE_13__ {TYPE_2__ hw; } ;
typedef  TYPE_5__ pc300_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_TTY_DBG (char*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  CPC_TTY_LOCK (TYPE_5__*,unsigned long) ; 
 int /*<<< orphan*/  CPC_TTY_UNLOCK (TYPE_5__*,unsigned long) ; 
 int /*<<< orphan*/  CTL ; 
 scalar_t__ M_REG (int /*<<< orphan*/ ,int) ; 
 unsigned char cpc_readb (scalar_t__) ; 
 int /*<<< orphan*/  cpc_writeb (scalar_t__,unsigned char) ; 

__attribute__((used)) static void cpc_tty_signal_on(pc300dev_t *pc300dev, unsigned char signal)
{
	pc300ch_t *pc300chan = (pc300ch_t *)pc300dev->chan; 
	pc300_t *card = (pc300_t *) pc300chan->card; 
	int ch = pc300chan->channel; 
	unsigned long flags; 

	CPC_TTY_DBG("%s-tty: Set signal %x\n",
		pc300dev->dev->name, signal);
	CPC_TTY_LOCK(card, flags); 
	cpc_writeb(card->hw.scabase + M_REG(CTL,ch), 
		cpc_readb(card->hw.scabase+M_REG(CTL,ch))& ~signal);
	CPC_TTY_UNLOCK(card,flags); 
}