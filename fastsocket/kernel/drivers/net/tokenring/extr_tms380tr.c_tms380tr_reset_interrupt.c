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
struct TYPE_2__ {unsigned short STS; unsigned short* Parm; } ;
struct net_local {TYPE_1__ ssb; } ;
struct net_device {int dummy; } ;
typedef  TYPE_1__ SSB ;

/* Variables and functions */
 int CMD_CLEAR_SYSTEM_IRQ ; 
 int CMD_SSB_CLEAR ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_exec_sifcmd (struct net_device*,int) ; 

__attribute__((used)) static void tms380tr_reset_interrupt(struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);
	SSB *ssb = &tp->ssb;

	/*
	 * [Workaround for "Data Late"]
	 * Set all fields of the SSB to well-defined values so we can
	 * check if the adapter has written the SSB.
	 */

	ssb->STS	= (unsigned short) -1;
	ssb->Parm[0] 	= (unsigned short) -1;
	ssb->Parm[1] 	= (unsigned short) -1;
	ssb->Parm[2] 	= (unsigned short) -1;

	/* Free SSB by issuing SSB_CLEAR command after reading IRQ code
	 * and clear STS_SYSTEM_IRQ bit: enable adapter for further interrupts.
	 */
	tms380tr_exec_sifcmd(dev, CMD_SSB_CLEAR | CMD_CLEAR_SYSTEM_IRQ);

	return;
}