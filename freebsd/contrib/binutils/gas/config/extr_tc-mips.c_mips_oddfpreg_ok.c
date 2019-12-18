#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mips_opcode {char* name; int pinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  isa; } ;

/* Variables and functions */
#define  FP_D 129 
#define  FP_S 128 
 int INSN_COPROC_MEMORY_DELAY ; 
 int INSN_COPROC_MOVE_DELAY ; 
 int INSN_LOAD_COPROC_DELAY ; 
 int INSN_MACRO ; 
 int INSN_STORE_MEMORY ; 
 scalar_t__ ISA_HAS_ODD_SINGLE_FPR (int /*<<< orphan*/ ) ; 
 TYPE_1__ mips_opts ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
mips_oddfpreg_ok (const struct mips_opcode *insn, int argnum)
{
  const char *s = insn->name;

  if (insn->pinfo == INSN_MACRO)
    /* Let a macro pass, we'll catch it later when it is expanded.  */
    return 1;

  if (ISA_HAS_ODD_SINGLE_FPR (mips_opts.isa))
    {
      /* Allow odd registers for single-precision ops.  */
      switch (insn->pinfo & (FP_S | FP_D))
	{
	case FP_S:
	case 0:
	  return 1;	/* both single precision - ok */
	case FP_D:
	  return 0;	/* both double precision - fail */
	default:
	  break;
	}

      /* Cvt.w.x and cvt.x.w allow an odd register for a 'w' or 's' operand.  */
      s = strchr (insn->name, '.');
      if (argnum == 2)
	s = s != NULL ? strchr (s + 1, '.') : NULL;
      return (s != NULL && (s[1] == 'w' || s[1] == 's'));
    } 

  /* Single-precision coprocessor loads and moves are OK too.  */
  if ((insn->pinfo & FP_S)
      && (insn->pinfo & (INSN_COPROC_MEMORY_DELAY | INSN_STORE_MEMORY
			 | INSN_LOAD_COPROC_DELAY | INSN_COPROC_MOVE_DELAY)))
    return 1;

  return 0;
}