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
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPLEX_TYPE ; 
 int /*<<< orphan*/  DECL_COMPLEX_GIMPLE_REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MTAG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
var_can_have_subvars (tree v)
{
  /* Volatile variables should never have subvars.  */
  if (TREE_THIS_VOLATILE (v))
    return false;

  /* Non decls or memory tags can never have subvars.  */
  if (!DECL_P (v) || MTAG_P (v))
    return false;

  /* Aggregates can have subvars.  */
  if (AGGREGATE_TYPE_P (TREE_TYPE (v)))
    return true;

  /* Complex types variables which are not also a gimple register can
    have subvars. */
  if (TREE_CODE (TREE_TYPE (v)) == COMPLEX_TYPE
      && !DECL_COMPLEX_GIMPLE_REG_P (v))
    return true;

  return false;
}