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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  ansi_opname (int) ; 
 int /*<<< orphan*/  build_cp_library_fn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushdecl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
push_cp_library_fn (enum tree_code operator_code, tree type)
{
  tree fn = build_cp_library_fn (ansi_opname (operator_code),
				 operator_code,
				 type);
  pushdecl (fn);
  return fn;
}