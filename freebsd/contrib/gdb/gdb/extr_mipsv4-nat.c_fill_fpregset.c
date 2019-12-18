#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * fp_regs; } ;
struct TYPE_6__ {unsigned int fp_csr; TYPE_1__ fp_r; } ;
typedef  TYPE_2__ fpregset_t ;
struct TYPE_7__ {int fp0; int fp_control_status; } ;

/* Variables and functions */
 size_t DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* mips_regnum (int /*<<< orphan*/ ) ; 

void
fill_fpregset (fpregset_t *fpregsetp, int regno)
{
  int regi;
  char *from, *to;

  for (regi = mips_regnum (current_gdbarch)->fp0;
       regi < mips_regnum (current_gdbarch)->fp0 + 32; regi++)
    {
      if ((regno == -1) || (regno == regi))
	{
	  from = (char *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (regi)];
	  to = (char *) &(fpregsetp->fp_r.fp_regs[regi - mips_regnum (current_gdbarch)->fp0]);
	  memcpy (to, from, DEPRECATED_REGISTER_RAW_SIZE (regi));
	}
    }

  if ((regno == -1)
      || (regno == mips_regnum (current_gdbarch)->fp_control_status))
    fpregsetp->fp_csr = *(unsigned *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (mips_regnum (current_gdbarch)->fp_control_status)];
}