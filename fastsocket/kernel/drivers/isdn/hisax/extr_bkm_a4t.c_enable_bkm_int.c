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
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__ ax; } ;
struct IsdnCardState {scalar_t__ typ; TYPE_2__ hw; } ;
struct TYPE_6__ {int i20IntCtrl; } ;
typedef  TYPE_3__ I20_REGISTER_FILE ;

/* Variables and functions */
 scalar_t__ ISDN_CTYPE_BKM_A4T ; 
 int intISDN ; 
 int intPCI ; 

__attribute__((used)) static void
enable_bkm_int(struct IsdnCardState *cs, unsigned bEnable)
{
	if (cs->typ == ISDN_CTYPE_BKM_A4T) {
		I20_REGISTER_FILE *pI20_Regs = (I20_REGISTER_FILE *) (cs->hw.ax.base);
		if (bEnable)
			pI20_Regs->i20IntCtrl |= (intISDN | intPCI);
		else
			/* CAUTION: This disables the video capture driver too */
			pI20_Regs->i20IntCtrl &= ~(intISDN | intPCI);
	}
}