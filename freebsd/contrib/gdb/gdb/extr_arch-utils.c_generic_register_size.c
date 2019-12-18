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
 int /*<<< orphan*/  DEPRECATED_REGISTER_VIRTUAL_TYPE (int) ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdbarch_register_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gdbarch_register_type_p (int /*<<< orphan*/ ) ; 

int
generic_register_size (int regnum)
{
  gdb_assert (regnum >= 0 && regnum < NUM_REGS + NUM_PSEUDO_REGS);
  if (gdbarch_register_type_p (current_gdbarch))
    return TYPE_LENGTH (gdbarch_register_type (current_gdbarch, regnum));
  else
    /* FIXME: cagney/2003-03-01: Once all architectures implement
       gdbarch_register_type(), this entire function can go away.  It
       is made obsolete by register_size().  */
    return TYPE_LENGTH (DEPRECATED_REGISTER_VIRTUAL_TYPE (regnum)); /* OK */
}