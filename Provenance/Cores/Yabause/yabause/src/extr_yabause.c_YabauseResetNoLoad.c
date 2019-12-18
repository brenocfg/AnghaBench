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

/* Variables and functions */
 int /*<<< orphan*/  Cs2Reset () ; 
 int /*<<< orphan*/  HighWram ; 
 int /*<<< orphan*/  LowWram ; 
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  SH2PowerOn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspReset () ; 
 int /*<<< orphan*/  ScuReset () ; 
 int /*<<< orphan*/  SmpcReset () ; 
 int /*<<< orphan*/  Vdp1Reset () ; 
 int /*<<< orphan*/  Vdp2Reset () ; 
 int /*<<< orphan*/  YabauseStopSlave () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void YabauseResetNoLoad(void) {
   SH2Reset(MSH2);
   YabauseStopSlave();
   memset(HighWram, 0, 0x100000);
   memset(LowWram, 0, 0x100000);

   // Reset CS0 area here
   // Reset CS1 area here
   Cs2Reset();
   ScuReset();
   ScspReset();
   Vdp1Reset();
   Vdp2Reset();
   SmpcReset();

   SH2PowerOn(MSH2);
}