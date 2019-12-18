#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_4__ {void* PC; void* SR; void** A; void** D; } ;
typedef  TYPE_1__ m68kregs_struct ;
typedef  int /*<<< orphan*/  YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68KGetRegisters (TYPE_1__*) ; 
 int /*<<< orphan*/  M68KSetRegisters (TYPE_1__*) ; 

__attribute__((used)) static void m68ksetRegister( YuiM68k *m68k, int nReg, u32 value ) {
  /* set register number <nReg> to value <value> in proc <m68k> */

  m68kregs_struct m68kregs;
  M68KGetRegisters(&m68kregs);

  if ( nReg < 8 ) m68kregs.D[nReg] = value;
  else if ( nReg < 16 ) m68kregs.A[nReg-8] = value;
  if ( nReg == 16 ) m68kregs.SR = value;
  if ( nReg == 17 ) m68kregs.PC = value;

  M68KSetRegisters(&m68kregs);
}