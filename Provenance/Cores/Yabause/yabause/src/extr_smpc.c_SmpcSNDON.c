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
struct TYPE_2__ {int* OREG; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68KStart () ; 
 TYPE_1__* SmpcRegs ; 

__attribute__((used)) static void SmpcSNDON(void) {
   M68KStart();
   SmpcRegs->OREG[31] = 0x6;
}