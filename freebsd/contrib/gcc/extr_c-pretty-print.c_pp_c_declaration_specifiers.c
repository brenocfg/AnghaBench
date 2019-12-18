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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_specifier_qualifier_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_function_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_storage_class_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_declaration_specifiers (c_pretty_printer *pp, tree t)
{
  pp_storage_class_specifier (pp, t);
  pp_function_specifier (pp, t);
  pp_c_specifier_qualifier_list (pp, DECL_P (t) ?  TREE_TYPE (t) : t);
}