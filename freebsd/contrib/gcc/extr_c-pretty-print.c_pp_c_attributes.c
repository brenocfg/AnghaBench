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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  pp_c_call_argument_list (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_tree_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_attributes (c_pretty_printer *pp, tree attributes)
{
  if (attributes == NULL_TREE)
    return;

  pp_c_identifier (pp, "__attribute__");
  pp_c_left_paren (pp);
  pp_c_left_paren (pp);
  for (; attributes != NULL_TREE; attributes = TREE_CHAIN (attributes))
    {
      pp_tree_identifier (pp, TREE_PURPOSE (attributes));
      if (TREE_VALUE (attributes))
	pp_c_call_argument_list (pp, TREE_VALUE (attributes));

      if (TREE_CHAIN (attributes))
	pp_separate_with (pp, ',');
    }
  pp_c_right_paren (pp);
  pp_c_right_paren (pp);
}