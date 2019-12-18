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
typedef  scalar_t__ rtx ;
typedef  int ds_t ;
struct TYPE_2__ {scalar_t__* operand; } ;

/* Variables and functions */
 int BEGIN_CONTROL ; 
 int BEGIN_DATA ; 
 int BEGIN_SPEC ; 
 scalar_t__ COND_EXEC ; 
 scalar_t__ COND_EXEC_CODE (scalar_t__) ; 
 scalar_t__ FP_REGNO_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GR_REGNO_P (int /*<<< orphan*/ ) ; 
 int MEM_P (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int SPEC_MODE_FOR_EXTEND_FIRST ; 
 int SPEC_MODE_FOR_EXTEND_LAST ; 
 int SPEC_MODE_INVALID ; 
 scalar_t__ UNSPEC ; 
 int UNSPEC_LDA ; 
 int UNSPEC_LDS ; 
 int UNSPEC_LDSA ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTEND ; 
 int /*<<< orphan*/  extract_insn_cached (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ia64_gen_spec_insn (scalar_t__,int,int,int,int) ; 
 int ia64_mode_to_int (int /*<<< orphan*/ ) ; 
 TYPE_1__ recog_data ; 

__attribute__((used)) static int
ia64_speculate_insn (rtx insn, ds_t ts, rtx *new_pat)
{  
  rtx pat, reg, mem, mem_reg;
  int mode_no, gen_p = 1;
  bool extend_p;
  
  gcc_assert (!(ts & ~BEGIN_SPEC) && ts);
           
  pat = PATTERN (insn);

  if (GET_CODE (pat) == COND_EXEC)
    pat = COND_EXEC_CODE (pat);

  /* This should be a SET ...  */
  if (GET_CODE (pat) != SET)
    return -1;

  reg = SET_DEST (pat);
  /* ... to the general/fp register ...  */
  if (!REG_P (reg) || !(GR_REGNO_P (REGNO (reg)) || FP_REGNO_P (REGNO (reg))))
    return -1;

  /* ... from the mem ...  */
  mem = SET_SRC (pat);

  /* ... that can, possibly, be a zero_extend ...  */
  if (GET_CODE (mem) == ZERO_EXTEND)
    {
      mem = XEXP (mem, 0);
      extend_p = true;      
    }
  else
    extend_p = false;

  /* ... or a speculative load.  */
  if (GET_CODE (mem) == UNSPEC)
    {
      int code;
      
      code = XINT (mem, 1);
      if (code != UNSPEC_LDA && code != UNSPEC_LDS && code != UNSPEC_LDSA)
	return -1;

      if ((code == UNSPEC_LDA && !(ts & BEGIN_CONTROL))
	  || (code == UNSPEC_LDS && !(ts & BEGIN_DATA))
	  || code == UNSPEC_LDSA)
	gen_p = 0;

      mem = XVECEXP (mem, 0, 0);
      gcc_assert (MEM_P (mem));
    }

  /* Source should be a mem ...  */
  if (!MEM_P (mem))
    return -1;

  /* ... addressed by a register.  */
  mem_reg = XEXP (mem, 0);
  if (!REG_P (mem_reg))
    return -1;
     
  /* We should use MEM's mode since REG's mode in presence of ZERO_EXTEND
     will always be DImode.  */
  mode_no = ia64_mode_to_int (GET_MODE (mem));
  
  if (mode_no == SPEC_MODE_INVALID
      || (extend_p
	  && !(SPEC_MODE_FOR_EXTEND_FIRST <= mode_no
	       && mode_no <= SPEC_MODE_FOR_EXTEND_LAST)))
    return -1;

  extract_insn_cached (insn);
  gcc_assert (reg == recog_data.operand[0] && mem == recog_data.operand[1]);

  *new_pat = ia64_gen_spec_insn (insn, ts, mode_no, gen_p != 0, extend_p);

  return gen_p;
}