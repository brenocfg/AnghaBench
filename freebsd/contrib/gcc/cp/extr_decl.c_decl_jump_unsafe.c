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
 scalar_t__ DECL_NONTRIVIALLY_INITIALIZED_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ pod_type_p (scalar_t__) ; 

__attribute__((used)) static int
decl_jump_unsafe (tree decl)
{
  if (TREE_CODE (decl) != VAR_DECL || TREE_STATIC (decl)
      || TREE_TYPE (decl) == error_mark_node)
    return 0;

  if (TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (decl))
      || DECL_NONTRIVIALLY_INITIALIZED_P (decl))
    return 2;

  if (pod_type_p (TREE_TYPE (decl)))
    return 0;

  /* The POD stuff is just pedantry; why should it matter if the class
     contains a field of pointer to member type?  */
  return 1;
}