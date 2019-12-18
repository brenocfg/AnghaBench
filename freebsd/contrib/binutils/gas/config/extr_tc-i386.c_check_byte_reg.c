#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int base_opcode; int* operand_types; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int operands; int* types; int /*<<< orphan*/  suffix; TYPE_3__ tm; TYPE_2__* op; } ;
struct TYPE_6__ {TYPE_1__* regs; } ;
struct TYPE_5__ {int reg_num; int /*<<< orphan*/  reg_name; } ;

/* Variables and functions */
 scalar_t__ CODE_64BIT ; 
 int Control ; 
 int Debug ; 
 int FloatAcc ; 
 int FloatReg ; 
 int InOutPortReg ; 
 int REGNAM_AL ; 
 int REGNAM_AX ; 
 int REGNAM_EAX ; 
 int Reg ; 
 int Reg16 ; 
 int Reg8 ; 
 int RegMMX ; 
 int RegXMM ; 
 int SReg2 ; 
 int SReg3 ; 
 int Test ; 
 int WordReg ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_code ; 
 TYPE_4__ i ; 
 scalar_t__ intel_syntax ; 
 int /*<<< orphan*/  quiet_warnings ; 
 int /*<<< orphan*/  register_prefix ; 

__attribute__((used)) static int
check_byte_reg (void)
{
  int op;

  for (op = i.operands; --op >= 0;)
    {
      /* If this is an eight bit register, it's OK.  If it's the 16 or
	 32 bit version of an eight bit register, we will just use the
	 low portion, and that's OK too.  */
      if (i.types[op] & Reg8)
	continue;

      /* movzx and movsx should not generate this warning.  */
      if (intel_syntax
	  && (i.tm.base_opcode == 0xfb7
	      || i.tm.base_opcode == 0xfb6
	      || i.tm.base_opcode == 0x63
	      || i.tm.base_opcode == 0xfbe
	      || i.tm.base_opcode == 0xfbf))
	continue;

      /* crc32 doesn't generate this warning.  */
      if (i.tm.base_opcode == 0xf20f38f0)
	continue;

      if ((i.types[op] & WordReg) && i.op[op].regs->reg_num < 4)
	{
	  /* Prohibit these changes in the 64bit mode, since the
	     lowering is more complicated.  */
	  if (flag_code == CODE_64BIT
	      && (i.tm.operand_types[op] & InOutPortReg) == 0)
	    {
	      as_bad (_("Incorrect register `%s%s' used with `%c' suffix"),
		      register_prefix, i.op[op].regs->reg_name,
		      i.suffix);
	      return 0;
	    }
#if REGISTER_WARNINGS
	  if (!quiet_warnings
	      && (i.tm.operand_types[op] & InOutPortReg) == 0)
	    as_warn (_("using `%s%s' instead of `%s%s' due to `%c' suffix"),
		     register_prefix,
		     (i.op[op].regs + (i.types[op] & Reg16
				       ? REGNAM_AL - REGNAM_AX
				       : REGNAM_AL - REGNAM_EAX))->reg_name,
		     register_prefix,
		     i.op[op].regs->reg_name,
		     i.suffix);
#endif
	  continue;
	}
      /* Any other register is bad.  */
      if (i.types[op] & (Reg | RegMMX | RegXMM
			 | SReg2 | SReg3
			 | Control | Debug | Test
			 | FloatReg | FloatAcc))
	{
	  as_bad (_("`%s%s' not allowed with `%s%c'"),
		  register_prefix,
		  i.op[op].regs->reg_name,
		  i.tm.name,
		  i.suffix);
	  return 0;
	}
    }
  return 1;
}