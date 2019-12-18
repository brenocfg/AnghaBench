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
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_VALUES (scalar_t__) ; 
 int /*<<< orphan*/  pp_c_type_cast (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_id_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
pp_c_enumeration_constant (c_pretty_printer *pp, tree e)
{
  bool value_is_named = true;
  tree type = TREE_TYPE (e);
  tree value;

  /* Find the name of this constant.  */
  for (value = TYPE_VALUES (type);
       value != NULL_TREE && !tree_int_cst_equal (TREE_VALUE (value), e);
       value = TREE_CHAIN (value))
    ;

  if (value != NULL_TREE)
    pp_id_expression (pp, TREE_PURPOSE (value));
  else
    {
      /* Value must have been cast.  */
      pp_c_type_cast (pp, type);
      value_is_named = false;
    }

  return value_is_named;
}