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
typedef  enum lvalue_use { ____Placeholder_lvalue_use } lvalue_use ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  G_ (char*) ; 
 int /*<<< orphan*/  READONLY_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_READONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int lv_asm ; 
 int lv_assign ; 
 int lv_decrement ; 
 int lv_increment ; 

__attribute__((used)) static void
readonly_error (tree arg, enum lvalue_use use)
{
  gcc_assert (use == lv_assign || use == lv_increment || use == lv_decrement
	      || use == lv_asm);
  /* Using this macro rather than (for example) arrays of messages
     ensures that all the format strings are checked at compile
     time.  */
#define READONLY_MSG(A, I, D, AS) (use == lv_assign ? (A)		\
				   : (use == lv_increment ? (I)		\
				   : (use == lv_decrement ? (D) : (AS))))
  if (TREE_CODE (arg) == COMPONENT_REF)
    {
      if (TYPE_READONLY (TREE_TYPE (TREE_OPERAND (arg, 0))))
	readonly_error (TREE_OPERAND (arg, 0), use);
      else
	error (READONLY_MSG (G_("assignment of read-only member %qD"),
			     G_("increment of read-only member %qD"),
			     G_("decrement of read-only member %qD"),
			     G_("read-only member %qD used as %<asm%> output")),
	       TREE_OPERAND (arg, 1));
    }
  else if (TREE_CODE (arg) == VAR_DECL)
    error (READONLY_MSG (G_("assignment of read-only variable %qD"),
			 G_("increment of read-only variable %qD"),
			 G_("decrement of read-only variable %qD"),
			 G_("read-only variable %qD used as %<asm%> output")),
	   arg);
  else
    error (READONLY_MSG (G_("assignment of read-only location"),
			 G_("increment of read-only location"),
			 G_("decrement of read-only location"),
			 G_("read-only location used as %<asm%> output")));
}