#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {scalar_t__ (* expand_decl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ORIGIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_unit_at_a_time ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  rest_of_decl_compilation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_one_static_var (tree var)
{
  /* In unit-at-a-time all the static variables are expanded at the end
     of compilation process.  */
  if (flag_unit_at_a_time)
    return;
  /* If this is an inlined copy of a static local variable,
     look up the original.  */
  var = DECL_ORIGIN (var);

  /* If we've already processed this variable because of that, do nothing.  */
  if (TREE_ASM_WRITTEN (var))
    return;

  /* Give the front end a chance to do whatever.  In practice, this is
     resolving duplicate names for IMA in C.  */
  if (lang_hooks.expand_decl (var))
    return;

  /* Otherwise, just emit the variable.  */
  rest_of_decl_compilation (var, 0, 0);
}