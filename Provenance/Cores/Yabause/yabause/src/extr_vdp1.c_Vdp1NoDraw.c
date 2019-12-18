#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ manualchange; } ;
struct TYPE_4__ {int EDSR; scalar_t__ COPR; } ;

/* Variables and functions */
 int /*<<< orphan*/  ScuSendDrawEnd () ; 
 TYPE_3__ Vdp1External ; 
 int /*<<< orphan*/  Vdp1FakeDrawCommands (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Vdp1Ram ; 
 TYPE_1__* Vdp1Regs ; 

void Vdp1NoDraw(void) {
   // beginning of a frame (ST-013-R3-061694 page 53)
   // BEF <- CEF
   // CEF <- 0
   Vdp1Regs->EDSR >>= 1;
   /* this should be done after a frame change or a plot trigger */
   Vdp1Regs->COPR = 0;

   Vdp1FakeDrawCommands(Vdp1Ram, Vdp1Regs);

   // we set two bits to 1
   Vdp1Regs->EDSR |= 2;
   ScuSendDrawEnd();
   Vdp1External.manualchange = 0;
}