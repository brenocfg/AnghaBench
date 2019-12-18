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
struct TYPE_4__ {int /*<<< orphan*/  (* Vdp1Reset ) () ;} ;
struct TYPE_3__ {int MODR; scalar_t__ PTMR; } ;

/* Variables and functions */
 TYPE_2__* VIDCore ; 
 TYPE_1__* Vdp1Regs ; 
 int /*<<< orphan*/  stub1 () ; 

void Vdp1Reset(void) {
   Vdp1Regs->PTMR = 0;
   Vdp1Regs->MODR = 0x1000; // VDP1 Version 1
   VIDCore->Vdp1Reset();
}