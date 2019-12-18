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
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_element_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_low_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_interesting_uses_op (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
idx_record_use (tree base, tree *idx,
		void *data)
{
  find_interesting_uses_op (data, *idx);
  if (TREE_CODE (base) == ARRAY_REF)
    {
      find_interesting_uses_op (data, array_ref_element_size (base));
      find_interesting_uses_op (data, array_ref_low_bound (base));
    }
  return true;
}