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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ REAL_EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  SET_REAL_EXP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconstpi ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ real_onep (int /*<<< orphan*/ ) ; 
 scalar_t__ real_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_atan (tree arglist, tree type)
{

  tree arg = TREE_VALUE (arglist);

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return NULL_TREE;

  /* Optimize atan(0.0) = 0.0.  */
  if (real_zerop (arg))
    return arg;

  /* Optimize atan(1.0) = pi/4.  */
  if (real_onep (arg))
    {
      REAL_VALUE_TYPE cst;

      real_convert (&cst, TYPE_MODE (type), &dconstpi);
      SET_REAL_EXP (&cst, REAL_EXP (&cst) - 2);
      return build_real (type, cst);
    }

  return NULL_TREE;
}