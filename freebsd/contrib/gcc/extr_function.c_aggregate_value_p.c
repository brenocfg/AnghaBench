#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {scalar_t__ (* return_in_memory ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
#define  CALL_EXPR 132 
 scalar_t__ DECL_BY_REFERENCE (scalar_t__) ; 
 scalar_t__ DECL_RESULT (scalar_t__) ; 
#define  FUNCTION_DECL 131 
#define  FUNCTION_TYPE 130 
#define  IDENTIFIER_NODE 129 
#define  METHOD_TYPE 128 
 scalar_t__ NULL_TREE ; 
 int const PARM_DECL ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int const RESULT_DECL ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 size_t TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/ * call_used_regs ; 
 scalar_t__ flag_pcc_struct_return ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  hard_function_value (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int** hard_regno_nregs ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 TYPE_2__ targetm ; 

int
aggregate_value_p (tree exp, tree fntype)
{
  int i, regno, nregs;
  rtx reg;

  tree type = (TYPE_P (exp)) ? exp : TREE_TYPE (exp);

  /* DECL node associated with FNTYPE when relevant, which we might need to
     check for by-invisible-reference returns, typically for CALL_EXPR input
     EXPressions.  */
  tree fndecl = NULL_TREE;
  
  if (fntype)
    switch (TREE_CODE (fntype))
      {
      case CALL_EXPR:
	fndecl = get_callee_fndecl (fntype);
	fntype = fndecl ? TREE_TYPE (fndecl) : 0;
	break;
      case FUNCTION_DECL:
	fndecl = fntype;
	fntype = TREE_TYPE (fndecl);
	break;
      case FUNCTION_TYPE:
      case METHOD_TYPE:
        break;
      case IDENTIFIER_NODE:
	fntype = 0;
	break;
      default:
	/* We don't expect other rtl types here.  */
	gcc_unreachable ();
      }

  if (TREE_CODE (type) == VOID_TYPE)
    return 0;

  /* If the front end has decided that this needs to be passed by
     reference, do so.  */
  if ((TREE_CODE (exp) == PARM_DECL || TREE_CODE (exp) == RESULT_DECL)
      && DECL_BY_REFERENCE (exp))
    return 1;

  /* If the EXPression is a CALL_EXPR, honor DECL_BY_REFERENCE set on the
     called function RESULT_DECL, meaning the function returns in memory by
     invisible reference.  This check lets front-ends not set TREE_ADDRESSABLE
     on the function type, which used to be the way to request such a return
     mechanism but might now be causing troubles at gimplification time if
     temporaries with the function type need to be created.  */
  if (TREE_CODE (exp) == CALL_EXPR && fndecl && DECL_RESULT (fndecl)
      && DECL_BY_REFERENCE (DECL_RESULT (fndecl)))
    return 1;
      
  if (targetm.calls.return_in_memory (type, fntype))
    return 1;
  /* Types that are TREE_ADDRESSABLE must be constructed in memory,
     and thus can't be returned in registers.  */
  if (TREE_ADDRESSABLE (type))
    return 1;
  if (flag_pcc_struct_return && AGGREGATE_TYPE_P (type))
    return 1;
  /* Make sure we have suitable call-clobbered regs to return
     the value in; if not, we must return it in memory.  */
  reg = hard_function_value (type, 0, fntype, 0);

  /* If we have something other than a REG (e.g. a PARALLEL), then assume
     it is OK.  */
  if (!REG_P (reg))
    return 0;

  regno = REGNO (reg);
  nregs = hard_regno_nregs[regno][TYPE_MODE (type)];
  for (i = 0; i < nregs; i++)
    if (! call_used_regs[regno + i])
      return 1;
  return 0;
}