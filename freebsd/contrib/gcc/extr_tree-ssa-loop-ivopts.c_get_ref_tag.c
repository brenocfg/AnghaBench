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
struct TYPE_4__ {scalar_t__ name_mem_tag; } ;
struct TYPE_3__ {scalar_t__ symbol_mem_tag; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 TYPE_2__* SSA_NAME_PTR_INFO (scalar_t__) ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 scalar_t__ SSA_VAR_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_base_address (scalar_t__) ; 
 scalar_t__ get_ref_base_and_extent (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_subvars_for_var (scalar_t__) ; 
 scalar_t__ handled_component_p (scalar_t__) ; 
 scalar_t__ unshare_expr (scalar_t__) ; 
 TYPE_1__* var_ann (scalar_t__) ; 

__attribute__((used)) static tree
get_ref_tag (tree ref, tree orig)
{
  tree var = get_base_address (ref);
  tree aref = NULL_TREE, tag, sv;
  HOST_WIDE_INT offset, size, maxsize;

  for (sv = orig; handled_component_p (sv); sv = TREE_OPERAND (sv, 0))
    {
      aref = get_ref_base_and_extent (sv, &offset, &size, &maxsize);
      if (ref)
	break;
    }

  if (aref && SSA_VAR_P (aref) && get_subvars_for_var (aref))
    return unshare_expr (sv);

  if (!var)
    return NULL_TREE;

  if (TREE_CODE (var) == INDIRECT_REF)
    {
      /* If the base is a dereference of a pointer, first check its name memory
	 tag.  If it does not have one, use its symbol memory tag.  */
      var = TREE_OPERAND (var, 0);
      if (TREE_CODE (var) != SSA_NAME)
	return NULL_TREE;

      if (SSA_NAME_PTR_INFO (var))
	{
	  tag = SSA_NAME_PTR_INFO (var)->name_mem_tag;
	  if (tag)
	    return tag;
	}
 
      var = SSA_NAME_VAR (var);
      tag = var_ann (var)->symbol_mem_tag;
      gcc_assert (tag != NULL_TREE);
      return tag;
    }
  else
    { 
      if (!DECL_P (var))
	return NULL_TREE;

      tag = var_ann (var)->symbol_mem_tag;
      if (tag)
	return tag;

      return var;
    }
}