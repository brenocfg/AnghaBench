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

/* Variables and functions */
 size_t NAMESPACE_DECL ; 
 size_t TEMPLATE_DECL ; 
 size_t TS_DECL_COMMON ; 
 size_t TS_DECL_MINIMAL ; 
 size_t TS_DECL_NON_COMMON ; 
 size_t TS_DECL_WITH_VIS ; 
 size_t TS_DECL_WRTL ; 
 size_t USING_DECL ; 
 int /*<<< orphan*/  init_shadowed_var_for_decl () ; 
 int** tree_contains_struct ; 

__attribute__((used)) static void
cp_init_ts (void)
{
  tree_contains_struct[NAMESPACE_DECL][TS_DECL_NON_COMMON] = 1;
  tree_contains_struct[USING_DECL][TS_DECL_NON_COMMON] = 1;
  tree_contains_struct[TEMPLATE_DECL][TS_DECL_NON_COMMON] = 1;

  tree_contains_struct[NAMESPACE_DECL][TS_DECL_WITH_VIS] = 1;
  tree_contains_struct[USING_DECL][TS_DECL_WITH_VIS] = 1;
  tree_contains_struct[TEMPLATE_DECL][TS_DECL_WITH_VIS] = 1;

  tree_contains_struct[NAMESPACE_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[USING_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[TEMPLATE_DECL][TS_DECL_WRTL] = 1;

  tree_contains_struct[NAMESPACE_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[USING_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[TEMPLATE_DECL][TS_DECL_COMMON] = 1;

  tree_contains_struct[NAMESPACE_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[USING_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[TEMPLATE_DECL][TS_DECL_MINIMAL] = 1;

  init_shadowed_var_for_decl ();

}