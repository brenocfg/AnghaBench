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
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  OPT_Wchar_subscripts ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ char_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
warn_array_subscript_with_type_char (tree index)
{
  if (TYPE_MAIN_VARIANT (TREE_TYPE (index)) == char_type_node
      && TREE_CODE (index) != INTEGER_CST)
    warning (OPT_Wchar_subscripts, "array subscript has type %<char%>");
}