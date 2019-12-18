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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/ * extract_muldiv_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static tree
extract_muldiv (tree t, tree c, enum tree_code code, tree wide_type,
		bool *strict_overflow_p)
{
  /* To avoid exponential search depth, refuse to allow recursion past
     three levels.  Beyond that (1) it's highly unlikely that we'll find
     something interesting and (2) we've probably processed it before
     when we built the inner expression.  */

  static int depth;
  tree ret;

  if (depth > 3)
    return NULL;

  depth++;
  ret = extract_muldiv_1 (t, c, code, wide_type, strict_overflow_p);
  depth--;

  return ret;
}