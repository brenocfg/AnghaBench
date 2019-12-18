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
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  (* elem_op_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  (* type_for_mode ) (int,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  build_word_mode_vector_type (int) ; 
 int /*<<< orphan*/  expand_vector_piecewise (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gimplify_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ word_mode ; 

__attribute__((used)) static tree
expand_vector_parallel (block_stmt_iterator *bsi, elem_op_func f, tree type,
			tree a, tree b,
			enum tree_code code)
{
  tree result, compute_type;
  enum machine_mode mode;
  int n_words = tree_low_cst (TYPE_SIZE_UNIT (type), 1) / UNITS_PER_WORD;

  /* We have three strategies.  If the type is already correct, just do
     the operation an element at a time.  Else, if the vector is wider than
     one word, do it a word at a time; finally, if the vector is smaller
     than one word, do it as a scalar.  */
  if (TYPE_MODE (TREE_TYPE (type)) == word_mode)
     return expand_vector_piecewise (bsi, f,
				     type, TREE_TYPE (type),
				     a, b, code);
  else if (n_words > 1)
    {
      tree word_type = build_word_mode_vector_type (n_words);
      result = expand_vector_piecewise (bsi, f,
				        word_type, TREE_TYPE (word_type),
					a, b, code);
      result = gimplify_val (bsi, word_type, result);
    }
  else
    {
      /* Use a single scalar operation with a mode no wider than word_mode.  */
      mode = mode_for_size (tree_low_cst (TYPE_SIZE (type), 1), MODE_INT, 0);
      compute_type = lang_hooks.types.type_for_mode (mode, 1);
      result = f (bsi, compute_type, a, b, NULL_TREE, NULL_TREE, code);
    }

  return result;
}