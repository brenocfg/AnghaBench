#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int PRINA; int PRINB; int PRIR; int /*<<< orphan*/  TVMD; } ;
struct TYPE_3__ {scalar_t__* priosused; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDGCDVdp2SetPriorityNBG0 (int) ; 
 int /*<<< orphan*/  VIDGCDVdp2SetPriorityNBG1 (int) ; 
 int /*<<< orphan*/  VIDGCDVdp2SetPriorityNBG2 (int) ; 
 int /*<<< orphan*/  VIDGCDVdp2SetPriorityNBG3 (int) ; 
 int /*<<< orphan*/  VIDGCDVdp2SetPriorityRBG0 (int) ; 
 int /*<<< orphan*/  VIDGCDVdp2SetResolution (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp1DrawPriority (int) ; 
 int /*<<< orphan*/  Vdp2DrawNBG0 () ; 
 int /*<<< orphan*/  Vdp2DrawNBG1 () ; 
 int /*<<< orphan*/  Vdp2DrawNBG2 () ; 
 int /*<<< orphan*/  Vdp2DrawNBG3 () ; 
 int /*<<< orphan*/  Vdp2DrawRBG0 () ; 
 TYPE_2__* Vdp2Regs ; 
 int nbg0priority ; 
 int nbg1priority ; 
 int nbg2priority ; 
 int nbg3priority ; 
 int rbg0priority ; 
 TYPE_1__ vdp1draw_info ; 

void VIDGCDVdp2DrawScreens(void)
{
   int i;

   VIDGCDVdp2SetResolution(Vdp2Regs->TVMD);
   VIDGCDVdp2SetPriorityNBG0(Vdp2Regs->PRINA & 0x7);
   VIDGCDVdp2SetPriorityNBG1((Vdp2Regs->PRINA >> 8) & 0x7);
   VIDGCDVdp2SetPriorityNBG2(Vdp2Regs->PRINB & 0x7);
   VIDGCDVdp2SetPriorityNBG3((Vdp2Regs->PRINB >> 8) & 0x7);
   VIDGCDVdp2SetPriorityRBG0(Vdp2Regs->PRIR & 0x7);

    /* Draw all the screens, from the lowest priority one forward. */
    for(i = 1; i < 8; ++i)
    {
        if (nbg3priority == i)
            Vdp2DrawNBG3();
        if (nbg2priority == i)
            Vdp2DrawNBG2();
        if (nbg1priority == i)
            Vdp2DrawNBG1();
        if (nbg0priority == i)
            Vdp2DrawNBG0();
        if (rbg0priority == i)
            Vdp2DrawRBG0();

        /* Draw anything in VDP1 that should be shown at this priority level. */
        if(vdp1draw_info.priosused[i])
            Vdp1DrawPriority(i);
        vdp1draw_info.priosused[i] = 0;
    }
}