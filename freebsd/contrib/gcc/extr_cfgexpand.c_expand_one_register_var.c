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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DECL_RTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  mark_reg_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_user_reg (int /*<<< orphan*/ ) ; 
 int promote_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_one_register_var (tree var)
{
  tree type = TREE_TYPE (var);
  int unsignedp = TYPE_UNSIGNED (type);
  enum machine_mode reg_mode
    = promote_mode (type, DECL_MODE (var), &unsignedp, 0);
  rtx x = gen_reg_rtx (reg_mode);

  SET_DECL_RTL (var, x);

  /* Note if the object is a user variable.  */
  if (!DECL_ARTIFICIAL (var))
    {
      mark_user_reg (x);

      /* Trust user variables which have a pointer type to really
	 be pointers.  Do not trust compiler generated temporaries
	 as our type system is totally busted as it relates to
	 pointer arithmetic which translates into lots of compiler
	 generated objects with pointer types, but which are not really
	 pointers.  */
      if (POINTER_TYPE_P (type))
	mark_reg_pointer (x, TYPE_ALIGN (TREE_TYPE (TREE_TYPE (var))));
    }
}