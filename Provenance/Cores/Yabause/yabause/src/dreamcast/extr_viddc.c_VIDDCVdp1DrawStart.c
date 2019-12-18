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
struct TYPE_2__ {int CLOFEN; int CLOFSL; int COBR; int COBG; int COBB; int COAR; int COAG; int COAB; } ;

/* Variables and functions */
 TYPE_1__* Vdp2Regs ; 
 int vdp1cob ; 
 int vdp1cog ; 
 int vdp1cor ; 

__attribute__((used)) static void VIDDCVdp1DrawStart(void)    {
    if(Vdp2Regs->CLOFEN & 0x40)    {
        // color offset enable
        if(Vdp2Regs->CLOFSL & 0x40)    {
            // color offset B
            vdp1cor = Vdp2Regs->COBR & 0xFF;
            if(Vdp2Regs->COBR & 0x100)
                vdp1cor |= 0xFFFFFF00;

            vdp1cog = Vdp2Regs->COBG & 0xFF;
            if(Vdp2Regs->COBG & 0x100)
                vdp1cog |= 0xFFFFFF00;

            vdp1cob = Vdp2Regs->COBB & 0xFF;
            if(Vdp2Regs->COBB & 0x100)
                vdp1cob |= 0xFFFFFF00;
        }
        else    {
            // color offset A
            vdp1cor = Vdp2Regs->COAR & 0xFF;
            if(Vdp2Regs->COAR & 0x100)
                vdp1cor |= 0xFFFFFF00;

            vdp1cog = Vdp2Regs->COAG & 0xFF;
            if(Vdp2Regs->COAG & 0x100)
                vdp1cog |= 0xFFFFFF00;

            vdp1cob = Vdp2Regs->COAB & 0xFF;
            if(Vdp2Regs->COAB & 0x100)
                vdp1cob |= 0xFFFFFF00;
        }
    }
    else // color offset disable
        vdp1cor = vdp1cog = vdp1cob = 0;
}