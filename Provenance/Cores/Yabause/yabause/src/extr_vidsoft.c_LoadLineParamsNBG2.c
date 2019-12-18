#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int specialprimode; int enable; int /*<<< orphan*/  PlaneAddr; } ;
typedef  TYPE_1__ vdp2draw_struct ;
struct TYPE_14__ {int /*<<< orphan*/  planetbl; } ;
typedef  TYPE_2__ screeninfo_struct ;
struct TYPE_15__ {int SFPRMD; int BGON; } ;
typedef  TYPE_3__ Vdp2 ;

/* Variables and functions */
 int /*<<< orphan*/  GeneratePlaneAddrTable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ReadVdp2ColorOffset (TYPE_3__*,TYPE_1__*,int,int) ; 
 TYPE_3__* Vdp2RestoreRegs (int,TYPE_3__*) ; 

__attribute__((used)) static void LoadLineParamsNBG2(vdp2draw_struct * info, screeninfo_struct * sinfo, int line, Vdp2* lines)
{
   Vdp2 * regs;

   regs = Vdp2RestoreRegs(line, lines);
   if (regs == NULL) return;
   ReadVdp2ColorOffset(regs, info, 0x4, 0x4);
   info->specialprimode = (regs->SFPRMD >> 4) & 0x3;
   info->enable = regs->BGON & 0x4;
   GeneratePlaneAddrTable(info, sinfo->planetbl, info->PlaneAddr, regs);
}