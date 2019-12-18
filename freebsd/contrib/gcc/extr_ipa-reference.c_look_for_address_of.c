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
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_base_var (int /*<<< orphan*/ ) ; 
 scalar_t__ has_proper_scope_for_analysis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_statics_escape ; 

__attribute__((used)) static void 
look_for_address_of (tree t)
{
  if (TREE_CODE (t) == ADDR_EXPR)
    {
      tree x = get_base_var (t);
      if (TREE_CODE (x) == VAR_DECL || TREE_CODE (x) == FUNCTION_DECL) 
	if (has_proper_scope_for_analysis (x))
	  bitmap_set_bit (module_statics_escape, DECL_UID (x));
    }
}