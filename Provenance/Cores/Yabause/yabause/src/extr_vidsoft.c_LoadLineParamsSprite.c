#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vdp2draw_struct ;
typedef  int /*<<< orphan*/  Vdp2 ;

/* Variables and functions */
 int /*<<< orphan*/  ReadVdp2ColorOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * Vdp2RestoreRegs (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LoadLineParamsSprite(vdp2draw_struct * info, int line, Vdp2* lines)
{
   Vdp2 * regs;

   regs = Vdp2RestoreRegs(line, lines);
   if (regs == NULL) return;
   ReadVdp2ColorOffset(regs, info, 0x40, 0x40);
}