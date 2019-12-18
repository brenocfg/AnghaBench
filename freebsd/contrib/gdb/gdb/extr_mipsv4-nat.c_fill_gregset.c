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
typedef  int /*<<< orphan*/ * gregset_t ;
typedef  int /*<<< orphan*/  greg_t ;
struct TYPE_2__ {int pc; int cause; int hi; int lo; } ;

/* Variables and functions */
 int CXT_CAUSE ; 
 int CXT_EPC ; 
 int CXT_MDHI ; 
 int CXT_MDLO ; 
 size_t DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 

void
fill_gregset (gregset_t *gregsetp, int regno)
{
  int regi;
  greg_t *regp = &(*gregsetp)[0];

  for (regi = 0; regi <= 32; regi++)
    if ((regno == -1) || (regno == regi))
      *(regp + regi) = *(greg_t *) & deprecated_registers[DEPRECATED_REGISTER_BYTE (regi)];

  if ((regno == -1) || (regno == mips_regnum (current_gdbarch)->pc))
    *(regp + CXT_EPC) = *(greg_t *) & deprecated_registers[DEPRECATED_REGISTER_BYTE (mips_regnum (current_gdbarch)->pc)];

  if ((regno == -1) || (regno == mips_regnum (current_gdbarch)->cause))
    *(regp + CXT_CAUSE) = *(greg_t *) & deprecated_registers[DEPRECATED_REGISTER_BYTE (mips_regnum (current_gdbarch)->cause)];

  if ((regno == -1) || (regno == mips_regnum (current_gdbarch)->hi))
    *(regp + CXT_MDHI) = *(greg_t *) & deprecated_registers[DEPRECATED_REGISTER_BYTE (mips_regnum (current_gdbarch)->hi)];

  if ((regno == -1) || (regno == mips_regnum (current_gdbarch)->lo))
    *(regp + CXT_MDLO) = *(greg_t *) & deprecated_registers[DEPRECATED_REGISTER_BYTE (mips_regnum (current_gdbarch)->lo)];
}