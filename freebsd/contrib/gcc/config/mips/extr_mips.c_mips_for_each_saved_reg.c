#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mips_save_restore_fn ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {TYPE_2__* machine; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmask; scalar_t__ fp_sp_offset; int /*<<< orphan*/  mask; scalar_t__ gp_sp_offset; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ BITSET_P (int /*<<< orphan*/ ,int) ; 
 int DFmode ; 
 int FP_INC ; 
 int FP_REG_FIRST ; 
 int FP_REG_LAST ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int GP_REG_FIRST ; 
 int GP_REG_LAST ; 
 int SFmode ; 
 scalar_t__ TARGET_SINGLE_FLOAT ; 
 TYPE_3__* cfun ; 
 int gpr_mode ; 
 int /*<<< orphan*/  mips_save_restore_reg (int,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_for_each_saved_reg (HOST_WIDE_INT sp_offset, mips_save_restore_fn fn)
{
#define BITSET_P(VALUE, BIT) (((VALUE) & (1L << (BIT))) != 0)

  enum machine_mode fpr_mode;
  HOST_WIDE_INT offset;
  int regno;

  /* Save registers starting from high to low.  The debuggers prefer at least
     the return register be stored at func+4, and also it allows us not to
     need a nop in the epilog if at least one register is reloaded in
     addition to return address.  */
  offset = cfun->machine->frame.gp_sp_offset - sp_offset;
  for (regno = GP_REG_LAST; regno >= GP_REG_FIRST; regno--)
    if (BITSET_P (cfun->machine->frame.mask, regno - GP_REG_FIRST))
      {
	mips_save_restore_reg (gpr_mode, regno, offset, fn);
	offset -= GET_MODE_SIZE (gpr_mode);
      }

  /* This loop must iterate over the same space as its companion in
     compute_frame_size.  */
  offset = cfun->machine->frame.fp_sp_offset - sp_offset;
  fpr_mode = (TARGET_SINGLE_FLOAT ? SFmode : DFmode);
  for (regno = (FP_REG_LAST - FP_INC + 1);
       regno >= FP_REG_FIRST;
       regno -= FP_INC)
    if (BITSET_P (cfun->machine->frame.fmask, regno - FP_REG_FIRST))
      {
	mips_save_restore_reg (fpr_mode, regno, offset, fn);
	offset -= GET_MODE_SIZE (fpr_mode);
      }
#undef BITSET_P
}