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
struct TYPE_2__ {scalar_t__ userclipX1; scalar_t__ userclipX2; scalar_t__ userclipY1; scalar_t__ userclipY2; scalar_t__ systemclipX1; scalar_t__ systemclipX2; scalar_t__ systemclipY1; scalar_t__ systemclipY2; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDP1LOG (char*) ; 
 TYPE_1__* Vdp1Regs ; 
 scalar_t__ vdp1clipxend ; 
 scalar_t__ vdp1clipxstart ; 
 scalar_t__ vdp1clipyend ; 
 scalar_t__ vdp1clipystart ; 

__attribute__((used)) static void PushUserClipping(int mode)
{
   if (mode == 1)
   {
      VDP1LOG("User clipping mode 1 not implemented\n");
      return;
   }

   vdp1clipxstart = Vdp1Regs->userclipX1;
   vdp1clipxend = Vdp1Regs->userclipX2;
   vdp1clipystart = Vdp1Regs->userclipY1;
   vdp1clipyend = Vdp1Regs->userclipY2;

   // This needs work
   if (vdp1clipxstart > Vdp1Regs->systemclipX1)
      vdp1clipxstart = Vdp1Regs->userclipX1;
   else
      vdp1clipxstart = Vdp1Regs->systemclipX1;

   if (vdp1clipxend < Vdp1Regs->systemclipX2)
      vdp1clipxend = Vdp1Regs->userclipX2;
   else
      vdp1clipxend = Vdp1Regs->systemclipX2;

   if (vdp1clipystart > Vdp1Regs->systemclipY1)
      vdp1clipystart = Vdp1Regs->userclipY1;
   else
      vdp1clipystart = Vdp1Regs->systemclipY1;

   if (vdp1clipyend < Vdp1Regs->systemclipY2)
      vdp1clipyend = Vdp1Regs->userclipY2;
   else
      vdp1clipyend = Vdp1Regs->systemclipY2;
}