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
typedef  int /*<<< orphan*/  gregset ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;
typedef  int /*<<< orphan*/  fpregset ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FP0_REGNUM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size, int which,
		      CORE_ADDR reg_addr)
{
  gdb_gregset_t gregset;
  gdb_fpregset_t fpregset;

  switch (which)
    {
    case 0:
      if (core_reg_size != sizeof (gregset))
	warning ("Wrong size gregset in core file.");
      else
	{
	  memcpy (&gregset, core_reg_sect, sizeof (gregset));
	  supply_gregset (&gregset);
	}
      break;

    case 2:
      if (core_reg_size != sizeof (fpregset))
	warning ("Wrong size fpregset in core file.");
      else
	{
	  memcpy (&fpregset, core_reg_sect, sizeof (fpregset));
	  if (FP0_REGNUM >= 0)
	    supply_fpregset (&fpregset);
	}
      break;

    default:
      /* We've covered all the kinds of registers we know about here,
         so this must be something we wouldn't know what to do with
         anyway.  Just ignore it.  */
      break;
    }
}