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
 scalar_t__ DECL_REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 

void
pp_c_storage_class_specifier (c_pretty_printer *pp, tree t)
{
  if (TREE_CODE (t) == TYPE_DECL)
    pp_c_identifier (pp, "typedef");
  else if (DECL_P (t))
    {
      if (DECL_REGISTER (t))
	pp_c_identifier (pp, "register");
      else if (TREE_STATIC (t) && TREE_CODE (t) == VAR_DECL)
	pp_c_identifier (pp, "static");
    }
}