#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int TVSTAT; } ;
struct TYPE_3__ {scalar_t__ IsSSH2Running; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH2SendInterrupt (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SSH2 ; 
 int /*<<< orphan*/  ScuSendHBlankIN () ; 
 TYPE_2__* Vdp2Regs ; 
 TYPE_1__ yabsys ; 

void Vdp2HBlankIN(void) {
   Vdp2Regs->TVSTAT |= 0x0004;
   ScuSendHBlankIN();

   if (yabsys.IsSSH2Running)
      SH2SendInterrupt(SSH2, 0x41, 0x2);
}