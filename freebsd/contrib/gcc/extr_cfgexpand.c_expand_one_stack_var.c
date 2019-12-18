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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_stack_frame_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_one_stack_var_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_decl_align_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
expand_one_stack_var (tree var)
{
  HOST_WIDE_INT size, offset, align;

  size = tree_low_cst (DECL_SIZE_UNIT (var), 1);
  align = get_decl_align_unit (var);
  offset = alloc_stack_frame_space (size, align);

  expand_one_stack_var_at (var, offset);
}