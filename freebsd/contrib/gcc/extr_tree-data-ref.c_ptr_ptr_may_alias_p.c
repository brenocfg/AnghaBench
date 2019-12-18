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
 scalar_t__ DR_MEMTAG (struct data_reference*) ; 
 struct ptr_info_def* DR_PTR_INFO (struct data_reference*) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SSA_NAME_VAR (scalar_t__) ; 
 TYPE_1__* get_var_ann (int /*<<< orphan*/ ) ; 
 int may_aliases_intersect (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
ptr_ptr_may_alias_p (tree ptr_a, tree ptr_b, 
		     struct data_reference *dra, 
		     struct data_reference *drb, 
		     bool *aliased)
{  
  tree tag_a = NULL_TREE, tag_b = NULL_TREE;
  struct ptr_info_def *pi_a = DR_PTR_INFO (dra);  
  struct ptr_info_def *pi_b = DR_PTR_INFO (drb);  

  if (pi_a && pi_a->name_mem_tag && pi_b && pi_b->name_mem_tag)
    {
      tag_a = pi_a->name_mem_tag;
      tag_b = pi_b->name_mem_tag;
    }
  else
    {
      tag_a = get_var_ann (SSA_NAME_VAR (ptr_a))->symbol_mem_tag;
      if (!tag_a)
	tag_a = DR_MEMTAG (dra);
      if (!tag_a)
	return false;
      
      tag_b = get_var_ann (SSA_NAME_VAR (ptr_b))->symbol_mem_tag;
      if (!tag_b)
	tag_b = DR_MEMTAG (drb);
      if (!tag_b)
	return false;
    }
  
  if (tag_a == tag_b)
    *aliased = true;
  else
    *aliased = may_aliases_intersect (tag_a, tag_b);
  
  return true;
}