#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* Vdp2DrawEnd ) () ;} ;
struct TYPE_9__ {scalar_t__ manualchange; } ;
struct TYPE_8__ {int EDSR; scalar_t__ COPR; } ;
struct TYPE_7__ {int TVSTAT; } ;
struct TYPE_6__ {scalar_t__ IsSSH2Running; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH2SendInterrupt (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SSH2 ; 
 int /*<<< orphan*/  ScuSendVBlankIN () ; 
 TYPE_5__* VIDCore ; 
 TYPE_4__ Vdp1External ; 
 TYPE_3__* Vdp1Regs ; 
 TYPE_2__* Vdp2Regs ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ yabsys ; 

void Vdp2VBlankIN(void) {
   VIDCore->Vdp2DrawEnd();
   /* this should be done after a frame change or a plot trigger */
   Vdp1Regs->COPR = 0;

   /* I'm not 100% sure about this, but it seems that when using manual change
   we should swap framebuffers in the "next field" and thus, clear the CEF...
   now we're lying a little here as we're not swapping the framebuffers. */
   if (Vdp1External.manualchange) Vdp1Regs->EDSR >>= 1;

   Vdp2Regs->TVSTAT |= 0x0008;
   ScuSendVBlankIN();

   if (yabsys.IsSSH2Running)
      SH2SendInterrupt(SSH2, 0x43, 0x6);
}