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
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_cached (int) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  registers_ptid ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 

__attribute__((used)) static void
legacy_read_register_gen (int regnum, char *myaddr)
{
  gdb_assert (regnum >= 0 && regnum < (NUM_REGS + NUM_PSEUDO_REGS));
  if (! ptid_equal (registers_ptid, inferior_ptid))
    {
      registers_changed ();
      registers_ptid = inferior_ptid;
    }

  if (!register_cached (regnum))
    target_fetch_registers (regnum);

  memcpy (myaddr, register_buffer (current_regcache, regnum),
	  DEPRECATED_REGISTER_RAW_SIZE (regnum));
}