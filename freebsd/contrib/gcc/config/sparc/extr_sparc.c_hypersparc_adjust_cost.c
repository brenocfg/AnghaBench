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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
#define  REG_DEP_ANTI 134 
 int REG_NOTE_KIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  TYPE_BRANCH 133 
 int TYPE_COMPARE ; 
 int TYPE_FPCMP ; 
#define  TYPE_FPLOAD 132 
#define  TYPE_FPSTORE 131 
 int TYPE_IALU ; 
#define  TYPE_LOAD 130 
 int TYPE_SHIFT ; 
#define  TYPE_SLOAD 129 
#define  TYPE_STORE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_attr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hypersparc_adjust_cost (rtx insn, rtx link, rtx dep_insn, int cost)
{
  enum attr_type insn_type, dep_type;
  rtx pat = PATTERN(insn);
  rtx dep_pat = PATTERN (dep_insn);

  if (recog_memoized (insn) < 0 || recog_memoized (dep_insn) < 0)
    return cost;

  insn_type = get_attr_type (insn);
  dep_type = get_attr_type (dep_insn);

  switch (REG_NOTE_KIND (link))
    {
    case 0:
      /* Data dependency; DEP_INSN writes a register that INSN reads some
	 cycles later.  */

      switch (insn_type)
	{
	case TYPE_STORE:
	case TYPE_FPSTORE:
	  /* Get the delay iff the address of the store is the dependence.  */
	  if (GET_CODE (pat) != SET || GET_CODE (dep_pat) != SET)
	    return cost;

	  if (rtx_equal_p (SET_DEST (dep_pat), SET_SRC (pat)))
	    return cost;
	  return cost + 3;

	case TYPE_LOAD:
	case TYPE_SLOAD:
	case TYPE_FPLOAD:
	  /* If a load, then the dependence must be on the memory address.  If
	     the addresses aren't equal, then it might be a false dependency */
	  if (dep_type == TYPE_STORE || dep_type == TYPE_FPSTORE)
	    {
	      if (GET_CODE (pat) != SET || GET_CODE (dep_pat) != SET
		  || GET_CODE (SET_DEST (dep_pat)) != MEM        
		  || GET_CODE (SET_SRC (pat)) != MEM
		  || ! rtx_equal_p (XEXP (SET_DEST (dep_pat), 0),
				    XEXP (SET_SRC (pat), 0)))
		return cost + 2;

	      return cost + 8;        
	    }
	  break;

	case TYPE_BRANCH:
	  /* Compare to branch latency is 0.  There is no benefit from
	     separating compare and branch.  */
	  if (dep_type == TYPE_COMPARE)
	    return 0;
	  /* Floating point compare to branch latency is less than
	     compare to conditional move.  */
	  if (dep_type == TYPE_FPCMP)
	    return cost - 1;
	  break;
	default:
	  break;
	}
	break;

    case REG_DEP_ANTI:
      /* Anti-dependencies only penalize the fpu unit.  */
      if (insn_type == TYPE_IALU || insn_type == TYPE_SHIFT)
        return 0;
      break;

    default:
      break;
    }    

  return cost;
}