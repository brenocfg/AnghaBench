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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int DECL_UID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_one_component_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvc_insert (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cvc_lookup (size_t) ; 

__attribute__((used)) static tree
get_component_var (tree var, bool imag_p)
{
  size_t decl_index = DECL_UID (var) * 2 + imag_p;
  tree ret = cvc_lookup (decl_index);

  if (ret == NULL)
    {
      ret = create_one_component_var (TREE_TYPE (TREE_TYPE (var)), var,
				      imag_p ? "CI" : "CR",
				      imag_p ? "$imag" : "$real",
				      imag_p ? IMAGPART_EXPR : REALPART_EXPR);
      cvc_insert (decl_index, ret);
    }

  return ret;
}