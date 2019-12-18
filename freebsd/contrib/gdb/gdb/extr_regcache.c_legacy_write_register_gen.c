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
 scalar_t__ CANNOT_STORE_REGISTER (int) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ real_register (int) ; 
 int /*<<< orphan*/  register_buffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ register_cached (int) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  registers_ptid ; 
 int /*<<< orphan*/  set_register_cached (int,int) ; 
 int /*<<< orphan*/  target_prepare_to_store () ; 
 int /*<<< orphan*/  target_store_registers (int) ; 

__attribute__((used)) static void
legacy_write_register_gen (int regnum, const void *myaddr)
{
  int size;
  gdb_assert (regnum >= 0 && regnum < (NUM_REGS + NUM_PSEUDO_REGS));

  /* On the sparc, writing %g0 is a no-op, so we don't even want to
     change the registers array if something writes to this register.  */
  if (CANNOT_STORE_REGISTER (regnum))
    return;

  if (! ptid_equal (registers_ptid, inferior_ptid))
    {
      registers_changed ();
      registers_ptid = inferior_ptid;
    }

  size = DEPRECATED_REGISTER_RAW_SIZE (regnum);

  if (real_register (regnum))
    {
      /* If we have a valid copy of the register, and new value == old
	 value, then don't bother doing the actual store. */
      if (register_cached (regnum)
	  && (memcmp (register_buffer (current_regcache, regnum), myaddr, size)
	      == 0))
	return;
      else
	target_prepare_to_store ();
    }

  memcpy (register_buffer (current_regcache, regnum), myaddr, size);

  set_register_cached (regnum, 1);
  target_store_registers (regnum);
}