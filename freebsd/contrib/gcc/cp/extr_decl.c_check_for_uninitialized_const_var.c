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
 scalar_t__ CP_TYPE_CONST_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NEEDS_CONSTRUCTING (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_for_uninitialized_const_var (tree decl)
{
  tree type = TREE_TYPE (decl);

  /* ``Unless explicitly declared extern, a const object does not have
     external linkage and must be initialized. ($8.4; $12.1)'' ARM
     7.1.6 */
  if (TREE_CODE (decl) == VAR_DECL
      && TREE_CODE (type) != REFERENCE_TYPE
      && CP_TYPE_CONST_P (type)
      && !TYPE_NEEDS_CONSTRUCTING (type)
      && !DECL_INITIAL (decl))
    error ("uninitialized const %qD", decl);
}