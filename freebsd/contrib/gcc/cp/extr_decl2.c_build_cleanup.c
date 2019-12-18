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
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ ARRAY_TYPE ; 
 int LOOKUP_DESTRUCTOR ; 
 int LOOKUP_NONVIRTUAL ; 
 int LOOKUP_NORMAL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_HAS_TRIVIAL_DESTRUCTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_mark_addressable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  mark_used (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfk_complete_destructor ; 

tree
build_cleanup (tree decl)
{
  tree temp;
  tree type = TREE_TYPE (decl);

  /* This function should only be called for declarations that really
     require cleanups.  */
  gcc_assert (!TYPE_HAS_TRIVIAL_DESTRUCTOR (type));

  /* Treat all objects with destructors as used; the destructor may do
     something substantive.  */
  mark_used (decl);

  if (TREE_CODE (type) == ARRAY_TYPE)
    temp = decl;
  else
    {
      cxx_mark_addressable (decl);
      temp = build1 (ADDR_EXPR, build_pointer_type (type), decl);
    }
  temp = build_delete (TREE_TYPE (temp), temp,
		       sfk_complete_destructor,
		       LOOKUP_NORMAL|LOOKUP_NONVIRTUAL|LOOKUP_DESTRUCTOR, 0);
  return temp;
}