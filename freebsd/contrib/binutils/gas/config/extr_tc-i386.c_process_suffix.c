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
struct TYPE_6__ {int opcode_modifier; int base_opcode; int* operand_types; int extension_opcode; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {scalar_t__ suffix; int* types; int operands; TYPE_2__ tm; int /*<<< orphan*/  rex; TYPE_1__* op; scalar_t__ reg_operands; } ;
struct TYPE_7__ {int reg_type; } ;
struct TYPE_5__ {TYPE_3__* regs; } ;

/* Variables and functions */
 unsigned int ADDR_PREFIX_OPCODE ; 
 int Acc ; 
 scalar_t__ BYTE_MNEM_SUFFIX ; 
#define  CODE_16BIT 130 
#define  CODE_32BIT 129 
#define  CODE_64BIT 128 
 unsigned int DATA_PREFIX_OPCODE ; 
 int DefaultSize ; 
 int FloatMF ; 
 int IgnoreSize ; 
 int InOutPortReg ; 
 int JumpAbsolute ; 
 int JumpByte ; 
 int JumpInterSegment ; 
 scalar_t__ LONG_DOUBLE_MNEM_SUFFIX ; 
 scalar_t__ LONG_MNEM_SUFFIX ; 
 int NoRex64 ; 
 unsigned int No_bSuf ; 
 unsigned int No_lSuf ; 
 unsigned int No_qSuf ; 
 unsigned int No_sSuf ; 
 unsigned int No_wSuf ; 
 unsigned int No_xSuf ; 
 scalar_t__ QWORD_MNEM_SUFFIX ; 
 int /*<<< orphan*/  REX_W ; 
 int Reg ; 
 int Reg16 ; 
 int Reg32 ; 
 int Reg64 ; 
 int Reg8 ; 
 int ShortForm ; 
 int Size16 ; 
 int Size32 ; 
 int Size64 ; 
 int W ; 
 scalar_t__ WORD_MNEM_SUFFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  add_prefix (unsigned int) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  check_byte_reg () ; 
 int /*<<< orphan*/  check_long_reg () ; 
 int /*<<< orphan*/  check_qword_reg () ; 
 int /*<<< orphan*/  check_word_reg () ; 
 int flag_code ; 
 TYPE_4__ i ; 
 scalar_t__ intel_syntax ; 
 scalar_t__ stackop_size ; 

__attribute__((used)) static int
process_suffix (void)
{
  /* If matched instruction specifies an explicit instruction mnemonic
     suffix, use it.  */
  if (i.tm.opcode_modifier & (Size16 | Size32 | Size64))
    {
      if (i.tm.opcode_modifier & Size16)
	i.suffix = WORD_MNEM_SUFFIX;
      else if (i.tm.opcode_modifier & Size64)
	i.suffix = QWORD_MNEM_SUFFIX;
      else
	i.suffix = LONG_MNEM_SUFFIX;
    }
  else if (i.reg_operands)
    {
      /* If there's no instruction mnemonic suffix we try to invent one
	 based on register operands.  */
      if (!i.suffix)
	{
	  /* We take i.suffix from the last register operand specified,
	     Destination register type is more significant than source
	     register type.  crc32 in SSE4.2 prefers source register
	     type. */
	  if (i.tm.base_opcode == 0xf20f38f1)
	    {
	      if ((i.types[0] & Reg))
		i.suffix = ((i.types[0] & Reg16) ? WORD_MNEM_SUFFIX :
			    LONG_MNEM_SUFFIX);
	    }
	  else if (i.tm.base_opcode == 0xf20f38f0)
	    {
	      if ((i.types[0] & Reg8))
		i.suffix = BYTE_MNEM_SUFFIX;
	    }

	  if (!i.suffix)
	    {
	      int op;

	      if (i.tm.base_opcode == 0xf20f38f1
		  || i.tm.base_opcode == 0xf20f38f0)
		{
		  /* We have to know the operand size for crc32.  */
		  as_bad (_("ambiguous memory operand size for `%s`"),
			  i.tm.name);
		  return 0;
		}

	      for (op = i.operands; --op >= 0;)
		if ((i.types[op] & Reg)
		    && !(i.tm.operand_types[op] & InOutPortReg))
		  {
		    i.suffix = ((i.types[op] & Reg8) ? BYTE_MNEM_SUFFIX :
				(i.types[op] & Reg16) ? WORD_MNEM_SUFFIX :
				(i.types[op] & Reg64) ? QWORD_MNEM_SUFFIX :
				LONG_MNEM_SUFFIX);
		    break;
		  }
	    }
	}
      else if (i.suffix == BYTE_MNEM_SUFFIX)
	{
	  if (!check_byte_reg ())
	    return 0;
	}
      else if (i.suffix == LONG_MNEM_SUFFIX)
	{
	  if (!check_long_reg ())
	    return 0;
	}
      else if (i.suffix == QWORD_MNEM_SUFFIX)
	{
	  if (!check_qword_reg ())
	    return 0;
	}
      else if (i.suffix == WORD_MNEM_SUFFIX)
	{
	  if (!check_word_reg ())
	    return 0;
	}
      else if (intel_syntax && (i.tm.opcode_modifier & IgnoreSize))
	/* Do nothing if the instruction is going to ignore the prefix.  */
	;
      else
	abort ();
    }
  else if ((i.tm.opcode_modifier & DefaultSize)
	   && !i.suffix
	   /* exclude fldenv/frstor/fsave/fstenv */
	   && (i.tm.opcode_modifier & No_sSuf))
    {
      i.suffix = stackop_size;
    }
  else if (intel_syntax
	   && !i.suffix
	   && ((i.tm.operand_types[0] & JumpAbsolute)
	       || (i.tm.opcode_modifier & (JumpByte|JumpInterSegment))
	       || (i.tm.base_opcode == 0x0f01 /* [ls][gi]dt */
		   && i.tm.extension_opcode <= 3)))
    {
      switch (flag_code)
	{
	case CODE_64BIT:
	  if (!(i.tm.opcode_modifier & No_qSuf))
	    {
	      i.suffix = QWORD_MNEM_SUFFIX;
	      break;
	    }
	case CODE_32BIT:
	  if (!(i.tm.opcode_modifier & No_lSuf))
	    i.suffix = LONG_MNEM_SUFFIX;
	  break;
	case CODE_16BIT:
	  if (!(i.tm.opcode_modifier & No_wSuf))
	    i.suffix = WORD_MNEM_SUFFIX;
	  break;
	}
    }

  if (!i.suffix)
    {
      if (!intel_syntax)
	{
	  if (i.tm.opcode_modifier & W)
	    {
	      as_bad (_("no instruction mnemonic suffix given and "
			"no register operands; can't size instruction"));
	      return 0;
	    }
	}
      else
	{
	  unsigned int suffixes = (~i.tm.opcode_modifier
				   & (No_bSuf
				      | No_wSuf
				      | No_lSuf
				      | No_sSuf
				      | No_xSuf
				      | No_qSuf));

	  if ((i.tm.opcode_modifier & W)
	      || ((suffixes & (suffixes - 1))
		  && !(i.tm.opcode_modifier & (DefaultSize | IgnoreSize))))
	    {
	      as_bad (_("ambiguous operand size for `%s'"), i.tm.name);
	      return 0;
	    }
	}
    }

  /* Change the opcode based on the operand size given by i.suffix;
     We don't need to change things for byte insns.  */

  if (i.suffix && i.suffix != BYTE_MNEM_SUFFIX)
    {
      /* It's not a byte, select word/dword operation.  */
      if (i.tm.opcode_modifier & W)
	{
	  if (i.tm.opcode_modifier & ShortForm)
	    i.tm.base_opcode |= 8;
	  else
	    i.tm.base_opcode |= 1;
	}

      /* Now select between word & dword operations via the operand
	 size prefix, except for instructions that will ignore this
	 prefix anyway.  */
      if (i.tm.base_opcode == 0x0f01 && i.tm.extension_opcode == 0xc8)
	{
	  /* monitor in SSE3 is a very special case. The default size
	     of AX is the size of mode. The address size override
	     prefix will change the size of AX.  */
	  if (i.op->regs[0].reg_type &
	      (flag_code == CODE_32BIT ? Reg16 : Reg32))
	    if (!add_prefix (ADDR_PREFIX_OPCODE))
	      return 0;
	}
      else if (i.suffix != QWORD_MNEM_SUFFIX
	       && i.suffix != LONG_DOUBLE_MNEM_SUFFIX
	       && !(i.tm.opcode_modifier & (IgnoreSize | FloatMF))
	       && ((i.suffix == LONG_MNEM_SUFFIX) == (flag_code == CODE_16BIT)
		   || (flag_code == CODE_64BIT
		       && (i.tm.opcode_modifier & JumpByte))))
	{
	  unsigned int prefix = DATA_PREFIX_OPCODE;

	  if (i.tm.opcode_modifier & JumpByte) /* jcxz, loop */
	    prefix = ADDR_PREFIX_OPCODE;

	  if (!add_prefix (prefix))
	    return 0;
	}

      /* Set mode64 for an operand.  */
      if (i.suffix == QWORD_MNEM_SUFFIX
	  && flag_code == CODE_64BIT
	  && (i.tm.opcode_modifier & NoRex64) == 0)
	{
	  /* Special case for xchg %rax,%rax.  It is NOP and doesn't
	     need rex64.  */
	  if (i.operands != 2
	      || i.types [0] != (Acc | Reg64)
	      || i.types [1] != (Acc | Reg64)
	      || i.tm.base_opcode != 0x90)
	    i.rex |= REX_W;
	}

      /* Size floating point instruction.  */
      if (i.suffix == LONG_MNEM_SUFFIX)
	if (i.tm.opcode_modifier & FloatMF)
	  i.tm.base_opcode ^= 4;
    }

  return 1;
}