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
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_FUNCTION_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctor_identifier ; 
 int /*<<< orphan*/  dtor_identifier ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int lookup_fnfields_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
class_method_index_for_fn (tree class_type, tree function)
{
  gcc_assert (TREE_CODE (function) == FUNCTION_DECL
	      || DECL_FUNCTION_TEMPLATE_P (function));

  return lookup_fnfields_1 (class_type,
			    DECL_CONSTRUCTOR_P (function) ? ctor_identifier :
			    DECL_DESTRUCTOR_P (function) ? dtor_identifier :
			    DECL_NAME (function));
}