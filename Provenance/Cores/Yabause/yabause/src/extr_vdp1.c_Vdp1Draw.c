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
struct TYPE_6__ {int /*<<< orphan*/  (* Vdp1DrawEnd ) () ;int /*<<< orphan*/  (* Vdp1DrawStart ) () ;} ;
struct TYPE_5__ {int /*<<< orphan*/  disptoggle; } ;
struct TYPE_4__ {int addr; int EDSR; int COPR; } ;

/* Variables and functions */
 int /*<<< orphan*/  ScuSendDrawEnd () ; 
 TYPE_3__* VIDCore ; 
 TYPE_2__ Vdp1External ; 
 int /*<<< orphan*/  Vdp1NoDraw () ; 
 TYPE_1__* Vdp1Regs ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void Vdp1Draw(void)
{
   if (!Vdp1External.disptoggle)
   {
      Vdp1NoDraw();
      return;
   }

   Vdp1Regs->addr = 0;

   // beginning of a frame
   // BEF <- CEF
   // CEF <- 0
   Vdp1Regs->EDSR >>= 1;
   /* this should be done after a frame change or a plot trigger */
   Vdp1Regs->COPR = 0;

   VIDCore->Vdp1DrawStart();

   // we set two bits to 1
   Vdp1Regs->EDSR |= 2;
   Vdp1Regs->COPR = Vdp1Regs->addr >> 3;
   ScuSendDrawEnd();
   VIDCore->Vdp1DrawEnd();
}