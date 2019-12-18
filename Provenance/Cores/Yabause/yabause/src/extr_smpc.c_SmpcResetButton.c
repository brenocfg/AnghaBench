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
struct TYPE_2__ {scalar_t__ resd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  SH2SendInterrupt (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* SmpcInternalVars ; 

void SmpcResetButton(void) {
   // If RESD isn't set, send an NMI request to the MSH2.
   if (SmpcInternalVars->resd)
      return;

   SH2SendInterrupt(MSH2, 0xB, 16);
}