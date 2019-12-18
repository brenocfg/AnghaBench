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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 size_t BUILT_IN_TRAP ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/ * build_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** implicit_built_in_decls ; 

__attribute__((used)) static tree
call_builtin_trap (void)
{
  tree fn = implicit_built_in_decls[BUILT_IN_TRAP];

  gcc_assert (fn != NULL);
  fn = build_call (fn, NULL_TREE);
  return fn;
}