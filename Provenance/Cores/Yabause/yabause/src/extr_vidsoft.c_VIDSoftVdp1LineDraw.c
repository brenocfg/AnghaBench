#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdp1cmd_struct ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ s16 ;
struct TYPE_6__ {int /*<<< orphan*/  addr; scalar_t__ localY; scalar_t__ localX; } ;
typedef  TYPE_1__ Vdp1 ;

/* Variables and functions */
 int /*<<< orphan*/  DrawLine (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ T1ReadWord (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp1ReadCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gouraudA ; 
 int /*<<< orphan*/  gouraudB ; 
 int /*<<< orphan*/  gouraudLineSetup (double*,double*,double*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iterateOverLine (int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void VIDSoftVdp1LineDraw(u8* ram, Vdp1*regs, u8* back_framebuffer)
{
	int x1, y1, x2, y2;
	double redstep = 0, greenstep = 0, bluestep = 0;
	int length;
   vdp1cmd_struct cmd;

   Vdp1ReadCommand(&cmd, regs->addr, ram);

	x1 = (int)regs->localX + (int)((s16)T1ReadWord(ram, regs->addr + 0x0C));
	y1 = (int)regs->localY + (int)((s16)T1ReadWord(ram, regs->addr + 0x0E));
	x2 = (int)regs->localX + (int)((s16)T1ReadWord(ram, regs->addr + 0x10));
	y2 = (int)regs->localY + (int)((s16)T1ReadWord(ram, regs->addr + 0x12));

   length = iterateOverLine(x1, y1, x2, y2, 1, NULL, NULL, regs, &cmd, ram, back_framebuffer);
   gouraudLineSetup(&redstep, &bluestep, &greenstep, length, gouraudA, gouraudB, ram, regs, &cmd, back_framebuffer);
   DrawLine(x1, y1, x2, y2, 0, 0, 0, redstep, greenstep, bluestep, regs, &cmd, ram, back_framebuffer);
}