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
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 unsigned int DECL_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 int GS_UNHANDLED ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int exact_log2 (unsigned int) ; 
 int gimplify_omp_atomic_fetch_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gimplify_omp_atomic_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gimplify_omp_atomic_pipeline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum gimplify_status
gimplify_omp_atomic (tree *expr_p, tree *pre_p)
{
  tree addr = TREE_OPERAND (*expr_p, 0);
  tree rhs = TREE_OPERAND (*expr_p, 1);
  tree type = TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (addr)));
  HOST_WIDE_INT index;

  /* Make sure the type is one of the supported sizes.  */
  index = tree_low_cst (TYPE_SIZE_UNIT (type), 1);
  index = exact_log2 (index);
  if (index >= 0 && index <= 4)
    {
      enum gimplify_status gs;
      unsigned int align;

      if (DECL_P (TREE_OPERAND (addr, 0)))
	align = DECL_ALIGN_UNIT (TREE_OPERAND (addr, 0));
      else if (TREE_CODE (TREE_OPERAND (addr, 0)) == COMPONENT_REF
	       && TREE_CODE (TREE_OPERAND (TREE_OPERAND (addr, 0), 1))
		  == FIELD_DECL)
	align = DECL_ALIGN_UNIT (TREE_OPERAND (TREE_OPERAND (addr, 0), 1));
      else
	align = TYPE_ALIGN_UNIT (type);

      /* __sync builtins require strict data alignment.  */
      if (exact_log2 (align) >= index)
	{
	  /* When possible, use specialized atomic update functions.  */
	  if (INTEGRAL_TYPE_P (type) || POINTER_TYPE_P (type))
	    {
	      gs = gimplify_omp_atomic_fetch_op (expr_p, addr, rhs, index);
	      if (gs != GS_UNHANDLED)
		return gs;
	    }

	  /* If we don't have specialized __sync builtins, try and implement
	     as a compare and swap loop.  */
	  gs = gimplify_omp_atomic_pipeline (expr_p, pre_p, addr, rhs, index);
	  if (gs != GS_UNHANDLED)
	    return gs;
	}
    }

  /* The ultimate fallback is wrapping the operation in a mutex.  */
  return gimplify_omp_atomic_mutex (expr_p, pre_p, addr, rhs);
}