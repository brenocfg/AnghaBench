#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int* operand_types; } ;
typedef  TYPE_3__ template ;
typedef  int offsetT ;
struct TYPE_10__ {TYPE_3__ const* end; TYPE_3__* start; } ;
struct TYPE_9__ {char suffix; int operands; int* types; scalar_t__* prefix; TYPE_2__* op; scalar_t__ reg_operands; } ;
struct TYPE_7__ {TYPE_1__* imms; } ;
struct TYPE_6__ {int X_op; int X_add_number; } ;

/* Variables and functions */
#define  BYTE_MNEM_SUFFIX 134 
 scalar_t__ CODE_16BIT ; 
 size_t DATA_PREFIX ; 
 int Imm ; 
 unsigned int Imm16 ; 
 unsigned int Imm32 ; 
 unsigned int Imm32S ; 
 unsigned int Imm64 ; 
 unsigned int Imm8 ; 
 unsigned int Imm8S ; 
#define  LONG_MNEM_SUFFIX 133 
#define  O_absent 132 
#define  O_constant 131 
#define  O_register 130 
#define  QWORD_MNEM_SUFFIX 129 
 int Reg ; 
 int Reg16 ; 
 int Reg32 ; 
 int Reg64 ; 
 int Reg8 ; 
#define  WORD_MNEM_SUFFIX 128 
 int /*<<< orphan*/  abort () ; 
 TYPE_5__* current_templates ; 
 scalar_t__ flag_code ; 
 TYPE_4__ i ; 
 unsigned int smallest_imm_type (int) ; 

__attribute__((used)) static void
optimize_imm (void)
{
  char guess_suffix = 0;
  int op;

  if (i.suffix)
    guess_suffix = i.suffix;
  else if (i.reg_operands)
    {
      /* Figure out a suffix from the last register operand specified.
	 We can't do this properly yet, ie. excluding InOutPortReg,
	 but the following works for instructions with immediates.
	 In any case, we can't set i.suffix yet.  */
      for (op = i.operands; --op >= 0;)
	if (i.types[op] & Reg)
	  {
	    if (i.types[op] & Reg8)
	      guess_suffix = BYTE_MNEM_SUFFIX;
	    else if (i.types[op] & Reg16)
	      guess_suffix = WORD_MNEM_SUFFIX;
	    else if (i.types[op] & Reg32)
	      guess_suffix = LONG_MNEM_SUFFIX;
	    else if (i.types[op] & Reg64)
	      guess_suffix = QWORD_MNEM_SUFFIX;
	    break;
	  }
    }
  else if ((flag_code == CODE_16BIT) ^ (i.prefix[DATA_PREFIX] != 0))
    guess_suffix = WORD_MNEM_SUFFIX;

  for (op = i.operands; --op >= 0;)
    if (i.types[op] & Imm)
      {
	switch (i.op[op].imms->X_op)
	  {
	  case O_constant:
	    /* If a suffix is given, this operand may be shortened.  */
	    switch (guess_suffix)
	      {
	      case LONG_MNEM_SUFFIX:
		i.types[op] |= Imm32 | Imm64;
		break;
	      case WORD_MNEM_SUFFIX:
		i.types[op] |= Imm16 | Imm32S | Imm32 | Imm64;
		break;
	      case BYTE_MNEM_SUFFIX:
		i.types[op] |= Imm16 | Imm8 | Imm8S | Imm32S | Imm32 | Imm64;
		break;
	      }

	    /* If this operand is at most 16 bits, convert it
	       to a signed 16 bit number before trying to see
	       whether it will fit in an even smaller size.
	       This allows a 16-bit operand such as $0xffe0 to
	       be recognised as within Imm8S range.  */
	    if ((i.types[op] & Imm16)
		&& (i.op[op].imms->X_add_number & ~(offsetT) 0xffff) == 0)
	      {
		i.op[op].imms->X_add_number =
		  (((i.op[op].imms->X_add_number & 0xffff) ^ 0x8000) - 0x8000);
	      }
	    if ((i.types[op] & Imm32)
		&& ((i.op[op].imms->X_add_number & ~(((offsetT) 2 << 31) - 1))
		    == 0))
	      {
		i.op[op].imms->X_add_number = ((i.op[op].imms->X_add_number
						^ ((offsetT) 1 << 31))
					       - ((offsetT) 1 << 31));
	      }
	    i.types[op] |= smallest_imm_type (i.op[op].imms->X_add_number);

	    /* We must avoid matching of Imm32 templates when 64bit
	       only immediate is available.  */
	    if (guess_suffix == QWORD_MNEM_SUFFIX)
	      i.types[op] &= ~Imm32;
	    break;

	  case O_absent:
	  case O_register:
	    abort ();

	    /* Symbols and expressions.  */
	  default:
	    /* Convert symbolic operand to proper sizes for matching, but don't
	       prevent matching a set of insns that only supports sizes other
	       than those matching the insn suffix.  */
	    {
	      unsigned int mask, allowed = 0;
	      const template *t;

	      for (t = current_templates->start;
		   t < current_templates->end;
		   ++t)
		allowed |= t->operand_types[op];
	      switch (guess_suffix)
		{
		case QWORD_MNEM_SUFFIX:
		  mask = Imm64 | Imm32S;
		  break;
		case LONG_MNEM_SUFFIX:
		  mask = Imm32;
		  break;
		case WORD_MNEM_SUFFIX:
		  mask = Imm16;
		  break;
		case BYTE_MNEM_SUFFIX:
		  mask = Imm8;
		  break;
		default:
		  mask = 0;
		  break;
		}
	      if (mask & allowed)
		i.types[op] &= mask;
	    }
	    break;
	  }
      }
}