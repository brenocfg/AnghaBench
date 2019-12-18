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
 size_t BUILT_IN_STRCAT ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  integer_all_onesp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strcat_chk (tree fndecl, tree arglist)
{
  tree dest, src, size, fn;
  const char *p;

  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE,
			 VOID_TYPE))
    return 0;

  dest = TREE_VALUE (arglist);
  src = TREE_VALUE (TREE_CHAIN (arglist));
  size = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  p = c_getstr (src);
  /* If the SRC parameter is "", return DEST.  */
  if (p && *p == '\0')
    return omit_one_operand (TREE_TYPE (TREE_TYPE (fndecl)), dest, src);

  if (! host_integerp (size, 1) || ! integer_all_onesp (size))
    return 0;

  arglist = build_tree_list (NULL_TREE, src);
  arglist = tree_cons (NULL_TREE, dest, arglist);

  /* If __builtin_strcat_chk is used, assume strcat is available.  */
  fn = built_in_decls[BUILT_IN_STRCAT];
  if (!fn)
    return 0;

  return build_function_call_expr (fn, arglist);
}