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
 unsigned int GLOBAL_POINTER_REGNUM ; 
 unsigned int GP_REG_FIRST ; 
 unsigned int GP_REG_LAST ; 
 unsigned int PIC_FUNCTION_ADDR_REGNUM ; 
 int /*<<< orphan*/  TARGET_ABICALLS ; 
 int /*<<< orphan*/  TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TARGET_NEWABI ; 
 scalar_t__* call_used_regs ; 
 scalar_t__ current_function_has_nonlocal_goto ; 
 scalar_t__ current_function_is_leaf ; 
 scalar_t__ current_function_profile ; 
 int /*<<< orphan*/  current_function_uses_const_pool ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  mips_function_has_gp_insn () ; 
 int /*<<< orphan*/ * regs_ever_live ; 

__attribute__((used)) static unsigned int
mips_global_pointer (void)
{
  unsigned int regno;

  /* $gp is always available in non-abicalls code.  */
  if (!TARGET_ABICALLS)
    return GLOBAL_POINTER_REGNUM;

  /* We must always provide $gp when it is used implicitly.  */
  if (!TARGET_EXPLICIT_RELOCS)
    return GLOBAL_POINTER_REGNUM;

  /* FUNCTION_PROFILER includes a jal macro, so we need to give it
     a valid gp.  */
  if (current_function_profile)
    return GLOBAL_POINTER_REGNUM;

  /* If the function has a nonlocal goto, $gp must hold the correct
     global pointer for the target function.  */
  if (current_function_has_nonlocal_goto)
    return GLOBAL_POINTER_REGNUM;

  /* If the gp is never referenced, there's no need to initialize it.
     Note that reload can sometimes introduce constant pool references
     into a function that otherwise didn't need them.  For example,
     suppose we have an instruction like:

	  (set (reg:DF R1) (float:DF (reg:SI R2)))

     If R2 turns out to be constant such as 1, the instruction may have a
     REG_EQUAL note saying that R1 == 1.0.  Reload then has the option of
     using this constant if R2 doesn't get allocated to a register.

     In cases like these, reload will have added the constant to the pool
     but no instruction will yet refer to it.  */
  if (!regs_ever_live[GLOBAL_POINTER_REGNUM]
      && !current_function_uses_const_pool
      && !mips_function_has_gp_insn ())
    return 0;

  /* We need a global pointer, but perhaps we can use a call-clobbered
     register instead of $gp.  */
  if (TARGET_NEWABI && current_function_is_leaf)
    for (regno = GP_REG_FIRST; regno <= GP_REG_LAST; regno++)
      if (!regs_ever_live[regno]
	  && call_used_regs[regno]
	  && !fixed_regs[regno]
	  && regno != PIC_FUNCTION_ADDR_REGNUM)
	return regno;

  return GLOBAL_POINTER_REGNUM;
}