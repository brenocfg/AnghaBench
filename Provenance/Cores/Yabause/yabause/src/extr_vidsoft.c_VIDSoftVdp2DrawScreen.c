#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  TVMD; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDSoftVdp2SetResolution (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2ColorRam ; 
 int /*<<< orphan*/  Vdp2DrawNBG0 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2DrawNBG1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2DrawNBG2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2DrawNBG3 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2DrawRBG0 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2Lines ; 
 int /*<<< orphan*/  Vdp2Ram ; 
 TYPE_1__* Vdp2Regs ; 
 int /*<<< orphan*/  cell_scroll_data ; 

void VIDSoftVdp2DrawScreen(int screen)
{
   VIDSoftVdp2SetResolution(Vdp2Regs->TVMD);

   switch(screen)
   {
      case 0:
         Vdp2DrawNBG0(Vdp2Lines, Vdp2Regs, Vdp2Ram, Vdp2ColorRam, cell_scroll_data);
         break;
      case 1:
         Vdp2DrawNBG1(Vdp2Lines, Vdp2Regs, Vdp2Ram, Vdp2ColorRam, cell_scroll_data);
         break;
      case 2:
         Vdp2DrawNBG2(Vdp2Lines, Vdp2Regs, Vdp2Ram, Vdp2ColorRam, cell_scroll_data);
         break;
      case 3:
         Vdp2DrawNBG3(Vdp2Lines, Vdp2Regs, Vdp2Ram, Vdp2ColorRam, cell_scroll_data);
         break;
      case 4:
         Vdp2DrawRBG0(Vdp2Lines, Vdp2Regs, Vdp2Ram, Vdp2ColorRam, cell_scroll_data);
         break;
   }
}