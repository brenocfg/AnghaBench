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
 int /*<<< orphan*/  SSA_NAME_IN_FREE_LIST (scalar_t__) ; 
 struct ptr_info_def* SSA_NAME_PTR_INFO (scalar_t__) ; 
 int /*<<< orphan*/  dsa_named_for (scalar_t__) ; 
 unsigned int num_ssa_names ; 
 scalar_t__ ssa_name (unsigned int) ; 

__attribute__((used)) static void
detect_strict_aliasing_named (void)
{
  unsigned int i;

  for (i = 1; i < num_ssa_names; i++)
    {
      tree ptr = ssa_name (i);
      struct ptr_info_def *pi;

      if (ptr == NULL_TREE)
	continue;

      pi = SSA_NAME_PTR_INFO (ptr);

      if (!SSA_NAME_IN_FREE_LIST (ptr) && pi && pi->name_mem_tag)
	dsa_named_for (ptr);
    }
}