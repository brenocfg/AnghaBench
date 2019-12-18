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
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_5__ {TYPE_1__ timer; } ;
struct TYPE_6__ {TYPE_2__ hfcpci; } ;
struct IsdnCardState {TYPE_3__ hw; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static void
hfcpci_Timer(struct IsdnCardState *cs)
{
	cs->hw.hfcpci.timer.expires = jiffies + 75;
	/* WD RESET */
/*      WriteReg(cs, HFCD_DATA, HFCD_CTMT, cs->hw.hfcpci.ctmt | 0x80);
   add_timer(&cs->hw.hfcpci.timer);
 */
}