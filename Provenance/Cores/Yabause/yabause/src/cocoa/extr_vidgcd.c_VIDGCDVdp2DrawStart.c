#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ yend; scalar_t__ xend; scalar_t__ ystart; scalar_t__ xstart; } ;
struct TYPE_9__ {int PRISA; int PRISB; int PRISC; int PRISD; int CRAOFB; int SPCTL; int CLOFEN; int CLOFSL; int COBR; int COBG; int COBB; int COAR; int COAG; int COAB; int CCCTL; int WCTLC; } ;
struct TYPE_7__ {int cor; int cog; int cob; int /*<<< orphan*/ * PostPixelFetchCalc; } ;
struct TYPE_8__ {int* prioritytable; int coloroffset; scalar_t__ linewnd1addr; scalar_t__ linewnd0addr; int /*<<< orphan*/  islinewindow; TYPE_4__* clip; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoColorCalc ; 
 int /*<<< orphan*/  DoColorCalcWithColorOffset ; 
 int /*<<< orphan*/  DoColorOffset ; 
 int /*<<< orphan*/  DoNothing ; 
 int /*<<< orphan*/  ReadLineWindowData (int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ReadWindowData (int,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Vdp2DrawBackScreen () ; 
 TYPE_3__* Vdp2Regs ; 
 TYPE_2__ vdp1draw_info ; 
 int vdp1spritetype ; 

void VIDGCDVdp2DrawStart(void)
{
    int wctl;
   Vdp2DrawBackScreen();

    vdp1draw_info.prioritytable[0] = Vdp2Regs->PRISA & 0x7;
    vdp1draw_info.prioritytable[1] = (Vdp2Regs->PRISA >> 8) & 0x7;
    vdp1draw_info.prioritytable[2] = Vdp2Regs->PRISB & 0x7;
    vdp1draw_info.prioritytable[3] = (Vdp2Regs->PRISB >> 8) & 0x7;
    vdp1draw_info.prioritytable[4] = Vdp2Regs->PRISC & 0x7;
    vdp1draw_info.prioritytable[5] = (Vdp2Regs->PRISC >> 8) & 0x7;
    vdp1draw_info.prioritytable[6] = Vdp2Regs->PRISD & 0x7;
    vdp1draw_info.prioritytable[7] = (Vdp2Regs->PRISD >> 8) & 0x7;

    vdp1draw_info.coloroffset = (Vdp2Regs->CRAOFB & 0x70) << 4;
    vdp1spritetype = Vdp2Regs->SPCTL & 0xF;

    if(Vdp2Regs->CLOFEN & 0x40) {
        // color offset enable
        if(Vdp2Regs->CLOFSL & 0x40) {
            // color offset B
            vdp1draw_info.info.cor = Vdp2Regs->COBR & 0xFF;
            if(Vdp2Regs->COBR & 0x100)
                vdp1draw_info.info.cor |= 0xFFFFFF00;

            vdp1draw_info.info.cog = Vdp2Regs->COBG & 0xFF;
            if(Vdp2Regs->COBG & 0x100)
                vdp1draw_info.info.cog |= 0xFFFFFF00;

            vdp1draw_info.info.cob = Vdp2Regs->COBB & 0xFF;
            if(Vdp2Regs->COBB & 0x100)
                vdp1draw_info.info.cob |= 0xFFFFFF00;
        }
        else {
            // color offset A
            vdp1draw_info.info.cor = Vdp2Regs->COAR & 0xFF;
            if(Vdp2Regs->COAR & 0x100)
                vdp1draw_info.info.cor |= 0xFFFFFF00;

            vdp1draw_info.info.cog = Vdp2Regs->COAG & 0xFF;
            if(Vdp2Regs->COAG & 0x100)
                vdp1draw_info.info.cog |= 0xFFFFFF00;

            vdp1draw_info.info.cob = Vdp2Regs->COAB & 0xFF;
            if(Vdp2Regs->COAB & 0x100)
                vdp1draw_info.info.cob |= 0xFFFFFF00;
        }

        if(vdp1draw_info.info.cor == 0 && vdp1draw_info.info.cog == 0 && vdp1draw_info.info.cob == 0) {
            if(Vdp2Regs->CCCTL & 0x40)
                vdp1draw_info.info.PostPixelFetchCalc = &DoColorCalc;
            else
                vdp1draw_info.info.PostPixelFetchCalc = &DoNothing;
        }
        else {
            if(Vdp2Regs->CCCTL & 0x40)
                vdp1draw_info.info.PostPixelFetchCalc = &DoColorCalcWithColorOffset;
            else
                vdp1draw_info.info.PostPixelFetchCalc = &DoColorOffset;
        }
    }
    else { // color offset disable
        if(Vdp2Regs->CCCTL & 0x40)
            vdp1draw_info.info.PostPixelFetchCalc = &DoColorCalc;
        else
            vdp1draw_info.info.PostPixelFetchCalc = &DoNothing;
    }

    wctl = Vdp2Regs->WCTLC >> 8;
    vdp1draw_info.clip[0].xstart = vdp1draw_info.clip[0].ystart = 0;
    vdp1draw_info.clip[0].xend = vdp1draw_info.clip[0].yend = 0;
    vdp1draw_info.clip[1].xstart = vdp1draw_info.clip[1].ystart = 0;
    vdp1draw_info.clip[1].xend = vdp1draw_info.clip[1].yend = 0;
    ReadWindowData(wctl, vdp1draw_info.clip, Vdp2Regs);
    vdp1draw_info.linewnd0addr = vdp1draw_info.linewnd1addr = 0;
    ReadLineWindowData(&vdp1draw_info.islinewindow, wctl, &vdp1draw_info.linewnd0addr, &vdp1draw_info.linewnd1addr, Vdp2Regs);
}