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
#define  NTO_REG_FLOAT 129 
#define  NTO_REG_GENERAL 128 
 int /*<<< orphan*/  i386nto_supply_fpregset (char*) ; 
 int /*<<< orphan*/  i386nto_supply_gregset (char*) ; 

__attribute__((used)) static void
i386nto_supply_regset (int regset, char *data)
{
  switch (regset)
    {
    case NTO_REG_GENERAL:	/* QNX has different ordering of GP regs than GDB.  */
      i386nto_supply_gregset (data);
      break;
    case NTO_REG_FLOAT:
      i386nto_supply_fpregset (data);
      break;
    }
}