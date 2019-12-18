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
struct gdbarch {int dummy; } ;
struct dwarf2_frame_state_reg {int /*<<< orphan*/  how; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF2_FRAME_REG_CFA ; 
 int /*<<< orphan*/  DWARF2_FRAME_REG_RA ; 
 int PC_REGNUM ; 
 int SP_REGNUM ; 

__attribute__((used)) static void
dwarf2_frame_default_init_reg (struct gdbarch *gdbarch, int regnum,
			       struct dwarf2_frame_state_reg *reg)
{
  /* If we have a register that acts as a program counter, mark it as
     a destination for the return address.  If we have a register that
     serves as the stack pointer, arrange for it to be filled with the
     call frame address (CFA).  The other registers are marked as
     unspecified.

     We copy the return address to the program counter, since many
     parts in GDB assume that it is possible to get the return address
     by unwinding the program counter register.  However, on ISA's
     with a dedicated return address register, the CFI usually only
     contains information to unwind that return address register.

     The reason we're treating the stack pointer special here is
     because in many cases GCC doesn't emit CFI for the stack pointer
     and implicitly assumes that it is equal to the CFA.  This makes
     some sense since the DWARF specification (version 3, draft 8,
     p. 102) says that:

     "Typically, the CFA is defined to be the value of the stack
     pointer at the call site in the previous frame (which may be
     different from its value on entry to the current frame)."

     However, this isn't true for all platforms supported by GCC
     (e.g. IBM S/390 and zSeries).  Those architectures should provide
     their own architecture-specific initialization function.  */

  if (regnum == PC_REGNUM)
    reg->how = DWARF2_FRAME_REG_RA;
  else if (regnum == SP_REGNUM)
    reg->how = DWARF2_FRAME_REG_CFA;
}