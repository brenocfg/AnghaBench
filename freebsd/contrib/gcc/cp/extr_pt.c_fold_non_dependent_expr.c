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
typedef  scalar_t__ tree ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  tf_error ; 
 scalar_t__ tsubst_copy_and_build (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  type_dependent_expression_p (scalar_t__) ; 
 int /*<<< orphan*/  value_dependent_expression_p (scalar_t__) ; 

tree
fold_non_dependent_expr (tree expr)
{
  if (expr == NULL_TREE)
    return NULL_TREE;

  /* If we're in a template, but EXPR isn't value dependent, simplify
     it.  We're supposed to treat:

       template <typename T> void f(T[1 + 1]);
       template <typename T> void f(T[2]);

     as two declarations of the same function, for example.  */
  if (processing_template_decl
      && !type_dependent_expression_p (expr)
      && !value_dependent_expression_p (expr))
    {
      HOST_WIDE_INT saved_processing_template_decl;

      saved_processing_template_decl = processing_template_decl;
      processing_template_decl = 0;
      expr = tsubst_copy_and_build (expr,
				    /*args=*/NULL_TREE,
				    tf_error,
				    /*in_decl=*/NULL_TREE,
				    /*function_p=*/false,
				    /*integral_constant_expression_p=*/true);
      processing_template_decl = saved_processing_template_decl;
    }
  return expr;
}