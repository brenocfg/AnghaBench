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
struct gdbarch_tdep {int dummy; } ;
typedef  int ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 scalar_t__ mips_mask_address_p (struct gdbarch_tdep*) ; 

__attribute__((used)) static CORE_ADDR
mips_addr_bits_remove (CORE_ADDR addr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  if (mips_mask_address_p (tdep) && (((ULONGEST) addr) >> 32 == 0xffffffffUL))
    /* This hack is a work-around for existing boards using PMON, the
       simulator, and any other 64-bit targets that doesn't have true
       64-bit addressing.  On these targets, the upper 32 bits of
       addresses are ignored by the hardware.  Thus, the PC or SP are
       likely to have been sign extended to all 1s by instruction
       sequences that load 32-bit addresses.  For example, a typical
       piece of code that loads an address is this:

       lui $r2, <upper 16 bits>
       ori $r2, <lower 16 bits>

       But the lui sign-extends the value such that the upper 32 bits
       may be all 1s.  The workaround is simply to mask off these
       bits.  In the future, gcc may be changed to support true 64-bit
       addressing, and this masking will have to be disabled.  */
    return addr &= 0xffffffffUL;
  else
    return addr;
}