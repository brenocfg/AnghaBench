#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct ptr_info_def {scalar_t__ name_mem_tag; } ;
struct data_reference {int dummy; } ;
struct TYPE_2__ {scalar_t__ symbol_mem_tag; } ;

/* Variables and functions */
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ DR_MEMTAG (struct data_reference*) ; 
 struct ptr_info_def* DR_PTR_INFO (struct data_reference*) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_var_ann (int /*<<< orphan*/ ) ; 
 int is_aliased_with (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
ptr_decl_may_alias_p (tree ptr, tree decl, 
		      struct data_reference *ptr_dr, 
		      bool *aliased)
{
  tree tag = NULL_TREE;
  struct ptr_info_def *pi = DR_PTR_INFO (ptr_dr);  

  gcc_assert (TREE_CODE (ptr) == SSA_NAME && DECL_P (decl));

  if (pi)
    tag = pi->name_mem_tag;
  if (!tag)
    tag = get_var_ann (SSA_NAME_VAR (ptr))->symbol_mem_tag;
  if (!tag)
    tag = DR_MEMTAG (ptr_dr);
  if (!tag)
    return false;
   
  *aliased = is_aliased_with (tag, decl);      
  return true;
}