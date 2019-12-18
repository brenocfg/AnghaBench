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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  ALIGN_INDIRECT_REF 155 
#define  ARRAY_RANGE_REF 154 
#define  ARRAY_REF 153 
#define  BIND_EXPR 152 
#define  BIT_FIELD_REF 151 
#define  COMPONENT_REF 150 
#define  COMPOUND_EXPR 149 
#define  COND_EXPR 148 
#define  FUNCTION_DECL 147 
#define  IMAGPART_EXPR 146 
#define  INDIRECT_REF 145 
#define  LABEL_DECL 144 
#define  MAX_EXPR 143 
#define  MIN_EXPR 142 
#define  MISALIGNED_INDIRECT_REF 141 
#define  MODIFY_EXPR 140 
 int NUM_TREE_CODES ; 
#define  OBJ_TYPE_REF 139 
#define  PARM_DECL 138 
#define  PREDECREMENT_EXPR 137 
#define  PREINCREMENT_EXPR 136 
#define  REALPART_EXPR 135 
#define  RESULT_DECL 134 
#define  SAVE_EXPR 133 
#define  SSA_NAME 132 
#define  TARGET_EXPR 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TRY_CATCH_EXPR 130 
#define  VAR_DECL 129 
#define  WITH_CLEANUP_EXPR 128 

__attribute__((used)) static bool
maybe_lvalue_p (tree x)
{
  /* We only need to wrap lvalue tree codes.  */
  switch (TREE_CODE (x))
  {
  case VAR_DECL:
  case PARM_DECL:
  case RESULT_DECL:
  case LABEL_DECL:
  case FUNCTION_DECL:
  case SSA_NAME:

  case COMPONENT_REF:
  case INDIRECT_REF:
  case ALIGN_INDIRECT_REF:
  case MISALIGNED_INDIRECT_REF:
  case ARRAY_REF:
  case ARRAY_RANGE_REF:
  case BIT_FIELD_REF:
  case OBJ_TYPE_REF:

  case REALPART_EXPR:
  case IMAGPART_EXPR:
  case PREINCREMENT_EXPR:
  case PREDECREMENT_EXPR:
  case SAVE_EXPR:
  case TRY_CATCH_EXPR:
  case WITH_CLEANUP_EXPR:
  case COMPOUND_EXPR:
  case MODIFY_EXPR:
  case TARGET_EXPR:
  case COND_EXPR:
  case BIND_EXPR:
  case MIN_EXPR:
  case MAX_EXPR:
    break;

  default:
    /* Assume the worst for front-end tree codes.  */
    if ((int)TREE_CODE (x) >= NUM_TREE_CODES)
      break;
    return false;
  }

  return true;
}