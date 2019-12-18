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
struct TYPE_2__ {int dotsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKTYPE_28MHZ ; 
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  SH2NMI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspReset () ; 
 int /*<<< orphan*/  ScuReset () ; 
 TYPE_1__* SmpcInternalVars ; 
 int /*<<< orphan*/  Vdp1Reset () ; 
 int /*<<< orphan*/  Vdp2Reset () ; 
 int /*<<< orphan*/  YabauseChangeTiming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabauseStopSlave () ; 

void SmpcCKCHG352(void) {
   // Reset VDP1, VDP2, SCU, and SCSP
   Vdp1Reset();
   Vdp2Reset();
   ScuReset();
   ScspReset();

   // Clear VDP1/VDP2 ram

   YabauseStopSlave();

   // change clock
   YabauseChangeTiming(CLKTYPE_28MHZ);

   // Set DOTSEL
   SmpcInternalVars->dotsel = 1;

   // Send NMI
   SH2NMI(MSH2);
}