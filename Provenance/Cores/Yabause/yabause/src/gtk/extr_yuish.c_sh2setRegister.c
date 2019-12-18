#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_7__ {void* all; } ;
struct TYPE_8__ {void* PC; void* PR; void* MACL; void* MACH; void* VBR; void* GBR; TYPE_1__ SR; void** R; } ;
typedef  TYPE_2__ sh2regs_struct ;
struct TYPE_9__ {int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_3__ YuiSh ;

/* Variables and functions */
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SH2SetRegisters (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void sh2setRegister( YuiSh *sh2, int nReg, u32 value ) {
  /* set register number <nReg> to value <value> in proc <sh2> */

  sh2regs_struct sh2regs;
  SH2GetRegisters(sh2->debugsh, &sh2regs);

  if ( nReg < 16 ) sh2regs.R[nReg] = value;
  switch ( nReg ) {
  case 16: sh2regs.SR.all = value; break;
  case 17: sh2regs.GBR = value; break;
  case 18: sh2regs.VBR = value; break;
  case 19: sh2regs.MACH = value; break;
  case 20: sh2regs.MACL = value; break;
  case 21: sh2regs.PR = value; break;
  case 22: sh2regs.PC = value; break;
  }

  SH2SetRegisters(sh2->debugsh, &sh2regs);
}