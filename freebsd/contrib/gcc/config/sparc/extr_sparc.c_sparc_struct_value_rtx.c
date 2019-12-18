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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 int STRUCT_VALUE_OFFSET ; 
 scalar_t__ TARGET_ARCH64 ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_stack_local (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_add3_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_sub3_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sparc_std_struct_return ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 
 int /*<<< orphan*/  struct_value_alias_set ; 

__attribute__((used)) static rtx
sparc_struct_value_rtx (tree fndecl, int incoming)
{
  if (TARGET_ARCH64)
    return 0;
  else
    {
      rtx mem;

      if (incoming)
	mem = gen_rtx_MEM (Pmode, plus_constant (frame_pointer_rtx,
						 STRUCT_VALUE_OFFSET));
      else
	mem = gen_rtx_MEM (Pmode, plus_constant (stack_pointer_rtx,
						 STRUCT_VALUE_OFFSET));

      /* Only follow the SPARC ABI for fixed-size structure returns. 
         Variable size structure returns are handled per the normal 
         procedures in GCC. This is enabled by -mstd-struct-return */
      if (incoming == 2 
	  && sparc_std_struct_return
	  && TYPE_SIZE_UNIT (TREE_TYPE (fndecl))
	  && TREE_CODE (TYPE_SIZE_UNIT (TREE_TYPE (fndecl))) == INTEGER_CST)
	{
	  /* We must check and adjust the return address, as it is
	     optional as to whether the return object is really
	     provided.  */
	  rtx ret_rtx = gen_rtx_REG (Pmode, 31);
	  rtx scratch = gen_reg_rtx (SImode);
	  rtx endlab = gen_label_rtx (); 

	  /* Calculate the return object size */
	  tree size = TYPE_SIZE_UNIT (TREE_TYPE (fndecl));
	  rtx size_rtx = GEN_INT (TREE_INT_CST_LOW (size) & 0xfff);
	  /* Construct a temporary return value */
	  rtx temp_val = assign_stack_local (Pmode, TREE_INT_CST_LOW (size), 0);

	  /* Implement SPARC 32-bit psABI callee returns struck checking
	     requirements: 
	    
	      Fetch the instruction where we will return to and see if
	     it's an unimp instruction (the most significant 10 bits
	     will be zero).  */
	  emit_move_insn (scratch, gen_rtx_MEM (SImode,
						plus_constant (ret_rtx, 8)));
	  /* Assume the size is valid and pre-adjust */
	  emit_insn (gen_add3_insn (ret_rtx, ret_rtx, GEN_INT (4)));
	  emit_cmp_and_jump_insns (scratch, size_rtx, EQ, const0_rtx, SImode, 0, endlab);
	  emit_insn (gen_sub3_insn (ret_rtx, ret_rtx, GEN_INT (4)));
	  /* Assign stack temp: 
	     Write the address of the memory pointed to by temp_val into
	     the memory pointed to by mem */
	  emit_move_insn (mem, XEXP (temp_val, 0));
	  emit_label (endlab);
	}

      set_mem_alias_set (mem, struct_value_alias_set);
      return mem;
    }
}