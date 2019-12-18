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

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ handled_component_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
array_ref_contains_indirect_ref (tree ref)
{
  gcc_assert (TREE_CODE (ref) == ARRAY_REF);

  do {
    ref = TREE_OPERAND (ref, 0);
  } while (handled_component_p (ref));

  return TREE_CODE (ref) == INDIRECT_REF;
}