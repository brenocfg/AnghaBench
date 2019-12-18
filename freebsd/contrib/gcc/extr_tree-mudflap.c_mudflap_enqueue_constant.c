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
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STRING_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_build_string (char*) ; 
 scalar_t__ mf_marked_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mudflap_register_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_in_bytes (int /*<<< orphan*/ ) ; 

void
mudflap_enqueue_constant (tree obj)
{
  tree object_size, varname;

  if (mf_marked_p (obj))
    return;

  if (TREE_CODE (obj) == STRING_CST)
    object_size = build_int_cst (NULL_TREE, TREE_STRING_LENGTH (obj));
  else
    object_size = size_in_bytes (TREE_TYPE (obj));

  if (TREE_CODE (obj) == STRING_CST)
    varname = mf_build_string ("string literal");
  else
    varname = mf_build_string ("constant");

  mudflap_register_call (obj, object_size, varname);
}