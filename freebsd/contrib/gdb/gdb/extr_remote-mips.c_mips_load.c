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
 scalar_t__ MON_IDT ; 
 size_t PC_REGNUM ; 
 int /*<<< orphan*/  bfd_get_start_address (scalar_t__) ; 
 int /*<<< orphan*/  clear_symtab_users () ; 
 scalar_t__* deprecated_register_valid ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ mips_exit_debug () ; 
 int /*<<< orphan*/  mips_initialize () ; 
 int /*<<< orphan*/  mips_load_srec (char*) ; 
 scalar_t__ mips_monitor ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  pmon_load_fast (char*) ; 
 int /*<<< orphan*/  write_pc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_load (char *file, int from_tty)
{
  /* Get the board out of remote debugging mode.  */
  if (mips_exit_debug ())
    error ("mips_load:  Couldn't get into monitor mode.");

  if (mips_monitor != MON_IDT)
    pmon_load_fast (file);
  else
    mips_load_srec (file);

  mips_initialize ();

  /* Finally, make the PC point at the start address */
  if (mips_monitor != MON_IDT)
    {
      /* Work around problem where PMON monitor updates the PC after a load
         to a different value than GDB thinks it has. The following ensures
         that the write_pc() WILL update the PC value: */
      deprecated_register_valid[PC_REGNUM] = 0;
    }
  if (exec_bfd)
    write_pc (bfd_get_start_address (exec_bfd));

  inferior_ptid = null_ptid;	/* No process now */

/* This is necessary because many things were based on the PC at the time that
   we attached to the monitor, which is no longer valid now that we have loaded
   new code (and just changed the PC).  Another way to do this might be to call
   normal_stop, except that the stack may not be valid, and things would get
   horribly confused... */

  clear_symtab_users ();
}