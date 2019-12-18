#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * fp_regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  fp_csr; TYPE_1__ fp_r; } ;
typedef  TYPE_2__ fpregset_t ;
struct TYPE_7__ {scalar_t__ fp_implementation_revision; scalar_t__ fp_control_status; scalar_t__ fp0; } ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_register (scalar_t__,char*) ; 

void
supply_fpregset (fpregset_t *fpregsetp)
{
  int regi;
  char zerobuf[MAX_REGISTER_SIZE];
  memset (zerobuf, 0, MAX_REGISTER_SIZE);

  for (regi = 0; regi < 32; regi++)
    supply_register (mips_regnum (current_gdbarch)->fp0 + regi,
		     (char *) &fpregsetp->fp_r.fp_regs[regi]);

  supply_register (mips_regnum (current_gdbarch)->fp_control_status,
		   (char *) &fpregsetp->fp_csr);

  /* FIXME: how can we supply FCRIR?  The ABI doesn't tell us. */
  supply_register (mips_regnum (current_gdbarch)->fp_implementation_revision,
		   zerobuf);
}