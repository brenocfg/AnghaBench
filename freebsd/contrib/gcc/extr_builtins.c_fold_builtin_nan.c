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
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_nan (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_nan (tree arglist, tree type, int quiet)
{
  REAL_VALUE_TYPE real;
  const char *str;

  if (!validate_arglist (arglist, POINTER_TYPE, VOID_TYPE))
    return 0;
  str = c_getstr (TREE_VALUE (arglist));
  if (!str)
    return 0;

  if (!real_nan (&real, str, quiet, TYPE_MODE (type)))
    return 0;

  return build_real (type, real);
}