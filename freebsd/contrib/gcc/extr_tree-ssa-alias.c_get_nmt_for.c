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
struct ptr_info_def {scalar_t__ name_mem_tag; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ create_memory_tag (scalar_t__,int) ; 
 struct ptr_info_def* get_ptr_info (scalar_t__) ; 

__attribute__((used)) static tree
get_nmt_for (tree ptr)
{
  struct ptr_info_def *pi = get_ptr_info (ptr);
  tree tag = pi->name_mem_tag;

  if (tag == NULL_TREE)
    tag = create_memory_tag (TREE_TYPE (TREE_TYPE (ptr)), false);
  return tag;
}