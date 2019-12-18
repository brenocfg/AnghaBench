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
typedef  int rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int REGNO ;
typedef  int INSN_CODE ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_INT ; 
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 size_t HARD_REGNO_CALLER_SAVE_MODE (int,int,size_t) ; 
 scalar_t__ HARD_REGNO_MODE_OK (int,int) ; 
 int HOST_BITS_PER_INT ; 
 int MAX_MACHINE_MODE ; 
 int MOVE_MAX_WORDS ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  PUT_MODE (int,int) ; 
 size_t Pmode ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 size_t VOIDmode ; 
 scalar_t__ base_reg_class (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_fixed_reg_set ; 
 int* call_fixed_regs ; 
 scalar_t__* call_used_regs ; 
 int constrain_operands (int) ; 
 int /*<<< orphan*/  extract_insn (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int gen_rtx_INSN (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gen_rtx_MEM (size_t,int) ; 
 int gen_rtx_PLUS (size_t,int,int /*<<< orphan*/ ) ; 
 int gen_rtx_REG (size_t,int) ; 
 int gen_rtx_SET (size_t,int,int) ; 
 int recog_memoized (int) ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 int** reg_restore_code ; 
 int** reg_save_code ; 
 size_t** regno_save_mode ; 
 int /*<<< orphan*/  strict_memory_address_p (size_t,int) ; 

void
init_caller_save (void)
{
  rtx addr_reg;
  int offset;
  rtx address;
  int i, j;
  enum machine_mode mode;
  rtx savepat, restpat;
  rtx test_reg, test_mem;
  rtx saveinsn, restinsn;

  /* First find all the registers that we need to deal with and all
     the modes that they can have.  If we can't find a mode to use,
     we can't have the register live over calls.  */

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      if (call_used_regs[i] && ! call_fixed_regs[i])
	{
	  for (j = 1; j <= MOVE_MAX_WORDS; j++)
	    {
	      regno_save_mode[i][j] = HARD_REGNO_CALLER_SAVE_MODE (i, j,
								   VOIDmode);
	      if (regno_save_mode[i][j] == VOIDmode && j == 1)
		{
		  call_fixed_regs[i] = 1;
		  SET_HARD_REG_BIT (call_fixed_reg_set, i);
		}
	    }
	}
      else
	regno_save_mode[i][1] = VOIDmode;
    }

  /* The following code tries to approximate the conditions under which
     we can easily save and restore a register without scratch registers or
     other complexities.  It will usually work, except under conditions where
     the validity of an insn operand is dependent on the address offset.
     No such cases are currently known.

     We first find a typical offset from some BASE_REG_CLASS register.
     This address is chosen by finding the first register in the class
     and by finding the smallest power of two that is a valid offset from
     that register in every mode we will use to save registers.  */

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if (TEST_HARD_REG_BIT
	(reg_class_contents
	 [(int) base_reg_class (regno_save_mode [i][1], PLUS, CONST_INT)], i))
      break;

  gcc_assert (i < FIRST_PSEUDO_REGISTER);

  addr_reg = gen_rtx_REG (Pmode, i);

  for (offset = 1 << (HOST_BITS_PER_INT / 2); offset; offset >>= 1)
    {
      address = gen_rtx_PLUS (Pmode, addr_reg, GEN_INT (offset));

      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (regno_save_mode[i][1] != VOIDmode
	  && ! strict_memory_address_p (regno_save_mode[i][1], address))
	  break;

      if (i == FIRST_PSEUDO_REGISTER)
	break;
    }

  /* If we didn't find a valid address, we must use register indirect.  */
  if (offset == 0)
    address = addr_reg;

  /* Next we try to form an insn to save and restore the register.  We
     see if such an insn is recognized and meets its constraints.

     To avoid lots of unnecessary RTL allocation, we construct all the RTL
     once, then modify the memory and register operands in-place.  */

  test_reg = gen_rtx_REG (VOIDmode, 0);
  test_mem = gen_rtx_MEM (VOIDmode, address);
  savepat = gen_rtx_SET (VOIDmode, test_mem, test_reg);
  restpat = gen_rtx_SET (VOIDmode, test_reg, test_mem);

  saveinsn = gen_rtx_INSN (VOIDmode, 0, 0, 0, 0, 0, savepat, -1, 0, 0);
  restinsn = gen_rtx_INSN (VOIDmode, 0, 0, 0, 0, 0, restpat, -1, 0, 0);

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (mode = 0 ; mode < MAX_MACHINE_MODE; mode++)
      if (HARD_REGNO_MODE_OK (i, mode))
	{
	  int ok;

	  /* Update the register number and modes of the register
	     and memory operand.  */
	  REGNO (test_reg) = i;
	  PUT_MODE (test_reg, mode);
	  PUT_MODE (test_mem, mode);

	  /* Force re-recognition of the modified insns.  */
	  INSN_CODE (saveinsn) = -1;
	  INSN_CODE (restinsn) = -1;

	  reg_save_code[i][mode] = recog_memoized (saveinsn);
	  reg_restore_code[i][mode] = recog_memoized (restinsn);

	  /* Now extract both insns and see if we can meet their
	     constraints.  */
	  ok = (reg_save_code[i][mode] != -1
		&& reg_restore_code[i][mode] != -1);
	  if (ok)
	    {
	      extract_insn (saveinsn);
	      ok = constrain_operands (1);
	      extract_insn (restinsn);
	      ok &= constrain_operands (1);
	    }

	  if (! ok)
	    {
	      reg_save_code[i][mode] = -1;
	      reg_restore_code[i][mode] = -1;
	    }
	}
      else
	{
	  reg_save_code[i][mode] = -1;
	  reg_restore_code[i][mode] = -1;
	}

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    for (j = 1; j <= MOVE_MAX_WORDS; j++)
      if (reg_save_code [i][regno_save_mode[i][j]] == -1)
	{
	  regno_save_mode[i][j] = VOIDmode;
	  if (j == 1)
	    {
	      call_fixed_regs[i] = 1;
	      SET_HARD_REG_BIT (call_fixed_reg_set, i);
	    }
	}
}