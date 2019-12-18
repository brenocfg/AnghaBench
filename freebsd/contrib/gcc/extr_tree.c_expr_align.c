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
#define  CLEANUP_POINT_EXPR 144 
#define  COMPOUND_EXPR 143 
#define  COND_EXPR 142 
#define  CONST_DECL 141 
#define  CONVERT_EXPR 140 
 unsigned int DECL_ALIGN (int /*<<< orphan*/ ) ; 
#define  FUNCTION_DECL 139 
#define  INIT_EXPR 138 
#define  LABEL_DECL 137 
 unsigned int MAX (unsigned int,unsigned int) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
#define  MODIFY_EXPR 136 
#define  NON_LVALUE_EXPR 135 
#define  NOP_EXPR 134 
#define  PARM_DECL 133 
#define  RESULT_DECL 132 
#define  SAVE_EXPR 131 
#define  TARGET_EXPR 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 129 
#define  WITH_CLEANUP_EXPR 128 
 int /*<<< orphan*/  gcc_assert (int) ; 

unsigned int
expr_align (tree t)
{
  unsigned int align0, align1;

  switch (TREE_CODE (t))
    {
    case NOP_EXPR:  case CONVERT_EXPR:  case NON_LVALUE_EXPR:
      /* If we have conversions, we know that the alignment of the
	 object must meet each of the alignments of the types.  */
      align0 = expr_align (TREE_OPERAND (t, 0));
      align1 = TYPE_ALIGN (TREE_TYPE (t));
      return MAX (align0, align1);

    case SAVE_EXPR:         case COMPOUND_EXPR:       case MODIFY_EXPR:
    case INIT_EXPR:         case TARGET_EXPR:         case WITH_CLEANUP_EXPR:
    case CLEANUP_POINT_EXPR:
      /* These don't change the alignment of an object.  */
      return expr_align (TREE_OPERAND (t, 0));

    case COND_EXPR:
      /* The best we can do is say that the alignment is the least aligned
	 of the two arms.  */
      align0 = expr_align (TREE_OPERAND (t, 1));
      align1 = expr_align (TREE_OPERAND (t, 2));
      return MIN (align0, align1);

      /* FIXME: LABEL_DECL and CONST_DECL never have DECL_ALIGN set
	 meaningfully, it's always 1.  */
    case LABEL_DECL:     case CONST_DECL:
    case VAR_DECL:       case PARM_DECL:   case RESULT_DECL:
    case FUNCTION_DECL:
      gcc_assert (DECL_ALIGN (t) != 0);
      return DECL_ALIGN (t);

    default:
      break;
    }

  /* Otherwise take the alignment from that of the type.  */
  return TYPE_ALIGN (TREE_TYPE (t));
}