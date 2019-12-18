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
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
#define  LEGACY_SIM_REGNO_IGNORE 129 
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  REGISTER_NAME (int) ; 
 int REGISTER_SIM_REGNO (int) ; 
#define  SIM_REGNO_DOES_NOT_EXIST 128 
 int /*<<< orphan*/  dump_mem (char*,int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdbsim_desc ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 int /*<<< orphan*/  set_register_cached (int,int) ; 
 int sim_fetch_register (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  sr_get_debug () ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
gdbsim_fetch_register (int regno)
{
  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	gdbsim_fetch_register (regno);
      return;
    }

  switch (REGISTER_SIM_REGNO (regno))
    {
    case LEGACY_SIM_REGNO_IGNORE:
      break;
    case SIM_REGNO_DOES_NOT_EXIST:
      {
	/* For moment treat a `does not exist' register the same way
           as an ``unavailable'' register.  */
	char buf[MAX_REGISTER_SIZE];
	int nr_bytes;
	memset (buf, 0, MAX_REGISTER_SIZE);
	supply_register (regno, buf);
	set_register_cached (regno, -1);
	break;
      }
    default:
      {
	static int warn_user = 1;
	char buf[MAX_REGISTER_SIZE];
	int nr_bytes;
	gdb_assert (regno >= 0 && regno < NUM_REGS);
	memset (buf, 0, MAX_REGISTER_SIZE);
	nr_bytes = sim_fetch_register (gdbsim_desc,
				       REGISTER_SIM_REGNO (regno),
				       buf, DEPRECATED_REGISTER_RAW_SIZE (regno));
	if (nr_bytes > 0 && nr_bytes != DEPRECATED_REGISTER_RAW_SIZE (regno) && warn_user)
	  {
	    fprintf_unfiltered (gdb_stderr,
				"Size of register %s (%d/%d) incorrect (%d instead of %d))",
				REGISTER_NAME (regno),
				regno, REGISTER_SIM_REGNO (regno),
				nr_bytes, DEPRECATED_REGISTER_RAW_SIZE (regno));
	    warn_user = 0;
	  }
	/* FIXME: cagney/2002-05-27: Should check `nr_bytes == 0'
	   indicating that GDB and the SIM have different ideas about
	   which registers are fetchable.  */
	/* Else if (nr_bytes < 0): an old simulator, that doesn't
	   think to return the register size.  Just assume all is ok.  */
	supply_register (regno, buf);
	if (sr_get_debug ())
	  {
	    printf_filtered ("gdbsim_fetch_register: %d", regno);
	    /* FIXME: We could print something more intelligible.  */
	    dump_mem (buf, DEPRECATED_REGISTER_RAW_SIZE (regno));
	  }
	break;
      }
    }
}