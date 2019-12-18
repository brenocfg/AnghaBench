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
struct cpwd {TYPE_1__* devs; scalar_t__ broken; } ;
struct TYPE_2__ {int /*<<< orphan*/  runstatus; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WD_INTR_OFF ; 
 scalar_t__ WD_STATUS ; 
 int /*<<< orphan*/  WD_STAT_BSTOP ; 
 int WD_S_RUNNING ; 
 int /*<<< orphan*/  cpwd_brokentimer (unsigned long) ; 
 int cpwd_readb (scalar_t__) ; 
 int /*<<< orphan*/  cpwd_toggleintr (struct cpwd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpwd_stoptimer(struct cpwd *p, int index)
{
	if (cpwd_readb(p->devs[index].regs + WD_STATUS) & WD_S_RUNNING) {
		cpwd_toggleintr(p, index, WD_INTR_OFF);

		if (p->broken) {
			p->devs[index].runstatus |= WD_STAT_BSTOP;
			cpwd_brokentimer((unsigned long) p);
		}
	}
}