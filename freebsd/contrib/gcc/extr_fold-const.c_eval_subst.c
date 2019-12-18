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
typedef  void* tree ;
typedef  enum tree_code_class { ____Placeholder_tree_code_class } tree_code_class ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  COMPOUND_EXPR 134 
#define  COND_EXPR 133 
#define  SAVE_EXPR 132 
 int TREE_CODE (void*) ; 
 int TREE_CODE_CLASS (int) ; 
 void* TREE_OPERAND (void*,int) ; 
 void* TREE_TYPE (void*) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_NOT_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 void* fold_build1 (int,void*,void*) ; 
 void* fold_build2 (int,void*,void*,void*) ; 
 void* fold_build3 (int,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  operand_equal_p (void*,void*,int /*<<< orphan*/ ) ; 
#define  tcc_binary 131 
#define  tcc_comparison 130 
#define  tcc_expression 129 
#define  tcc_unary 128 

__attribute__((used)) static tree
eval_subst (tree arg, tree old0, tree new0, tree old1, tree new1)
{
  tree type = TREE_TYPE (arg);
  enum tree_code code = TREE_CODE (arg);
  enum tree_code_class class = TREE_CODE_CLASS (code);

  /* We can handle some of the tcc_expression cases here.  */
  if (class == tcc_expression && code == TRUTH_NOT_EXPR)
    class = tcc_unary;
  else if (class == tcc_expression
	   && (code == TRUTH_ANDIF_EXPR || code == TRUTH_ORIF_EXPR))
    class = tcc_binary;

  switch (class)
    {
    case tcc_unary:
      return fold_build1 (code, type,
			  eval_subst (TREE_OPERAND (arg, 0),
				      old0, new0, old1, new1));

    case tcc_binary:
      return fold_build2 (code, type,
			  eval_subst (TREE_OPERAND (arg, 0),
				      old0, new0, old1, new1),
			  eval_subst (TREE_OPERAND (arg, 1),
				      old0, new0, old1, new1));

    case tcc_expression:
      switch (code)
	{
	case SAVE_EXPR:
	  return eval_subst (TREE_OPERAND (arg, 0), old0, new0, old1, new1);

	case COMPOUND_EXPR:
	  return eval_subst (TREE_OPERAND (arg, 1), old0, new0, old1, new1);

	case COND_EXPR:
	  return fold_build3 (code, type,
			      eval_subst (TREE_OPERAND (arg, 0),
					  old0, new0, old1, new1),
			      eval_subst (TREE_OPERAND (arg, 1),
					  old0, new0, old1, new1),
			      eval_subst (TREE_OPERAND (arg, 2),
					  old0, new0, old1, new1));
	default:
	  break;
	}
      /* Fall through - ???  */

    case tcc_comparison:
      {
	tree arg0 = TREE_OPERAND (arg, 0);
	tree arg1 = TREE_OPERAND (arg, 1);

	/* We need to check both for exact equality and tree equality.  The
	   former will be true if the operand has a side-effect.  In that
	   case, we know the operand occurred exactly once.  */

	if (arg0 == old0 || operand_equal_p (arg0, old0, 0))
	  arg0 = new0;
	else if (arg0 == old1 || operand_equal_p (arg0, old1, 0))
	  arg0 = new1;

	if (arg1 == old0 || operand_equal_p (arg1, old0, 0))
	  arg1 = new0;
	else if (arg1 == old1 || operand_equal_p (arg1, old1, 0))
	  arg1 = new1;

	return fold_build2 (code, type, arg0, arg1);
      }

    default:
      return arg;
    }
}