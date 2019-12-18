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
 int FRAME_POINTER_REGNUM ; 
 int HARD_FRAME_POINTER_REGNUM ; 
 int STACK_POINTER_REGNUM ; 
 int* call_really_used_regs ; 
 int* call_used_regs ; 
 int decode_reg_name (char const*) ; 
 int /*<<< orphan*/  error (char*,char const*,char const* const) ; 
 int* fixed_regs ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char const*) ; 

void
fix_register (const char *name, int fixed, int call_used)
{
  int i;

  /* Decode the name and update the primary form of
     the register info.  */

  if ((i = decode_reg_name (name)) >= 0)
    {
      if ((i == STACK_POINTER_REGNUM
#ifdef HARD_FRAME_POINTER_REGNUM
	   || i == HARD_FRAME_POINTER_REGNUM
#else
	   || i == FRAME_POINTER_REGNUM
#endif
	   )
	  && (fixed == 0 || call_used == 0))
	{
	  static const char * const what_option[2][2] = {
	    { "call-saved", "call-used" },
	    { "no-such-option", "fixed" }};

	  error ("can't use '%s' as a %s register", name,
		 what_option[fixed][call_used]);
	}
      else
	{
	  fixed_regs[i] = fixed;
	  call_used_regs[i] = call_used;
#ifdef CALL_REALLY_USED_REGISTERS
	  if (fixed == 0)
	    call_really_used_regs[i] = call_used;
#endif
	}
    }
  else
    {
      warning (0, "unknown register name: %s", name);
    }
}