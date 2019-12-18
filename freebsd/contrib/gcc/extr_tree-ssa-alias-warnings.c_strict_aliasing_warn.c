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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCATION_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCATION_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wstrict_aliasing ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ already_warned_in_frontend_p (int /*<<< orphan*/ ) ; 
 scalar_t__ contains_artificial_name_p (int /*<<< orphan*/ ) ; 
 scalar_t__ contains_node_type_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ find_first_artificial_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_main_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_maybe_star_prefix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_otype (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_ssa_base (int /*<<< orphan*/ ) ; 
 char* get_var_name (int /*<<< orphan*/ ) ; 
 scalar_t__ is_method_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_find_missing_stmts (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
strict_aliasing_warn (tree alias_site,
                      tree object1, bool is_ptr1,
                      tree object2, bool is_ptr2,
		      bool filter_artificials)
{
  tree ref_site1 = NULL_TREE;
  tree ref_site2 = NULL_TREE;
  const char *name1;
  const char *name2;
  location_t alias_loc;
  location_t ref1_loc;
  location_t ref2_loc;
  gcc_assert (object1);
  gcc_assert (object2);

  if (contains_artificial_name_p (object1)
      || contains_artificial_name_p (object2))
    return false;

  name1 = get_var_name (object1);
  name2 = get_var_name (object2);

  if (is_method_pointer (get_main_type (TREE_TYPE (object2))))
    return false;

  maybe_find_missing_stmts (object1, is_ptr1, object2, is_ptr2, &alias_site,
                            &ref_site1, &ref_site2);

  if (!alias_site)
    return false;

  if (EXPR_HAS_LOCATION (alias_site))
    alias_loc = EXPR_LOCATION (alias_site);
  else
    return false;

  if (EXPR_HAS_LOCATION (ref_site1))
    ref1_loc = EXPR_LOCATION (ref_site1);
  else
    ref1_loc = alias_loc;

  if (EXPR_HAS_LOCATION (ref_site2))
    ref2_loc = EXPR_LOCATION (ref_site2);
  else
    ref2_loc = alias_loc;

  if (already_warned_in_frontend_p (alias_site))
    return false;

  /* If they are not SSA names, but contain SSA names, drop the warning
     because it cannot be displayed well.
     Also drop it if they both contain artificials.
     XXX: this is a hack, must figure out a better way to display them.  */
  if (filter_artificials)
    if ((find_first_artificial_name (get_ssa_base (object1))
	 && find_first_artificial_name (get_ssa_base (object2)))
	|| (TREE_CODE (object1) != SSA_NAME
	    && contains_node_type_p (object1, SSA_NAME))
	|| (TREE_CODE (object2) != SSA_NAME
	    && contains_node_type_p (object2, SSA_NAME)))
      return false;

  /* XXX: In the following format string, %s:%d should be replaced by %H.
     However, in my tests only the first %H printed ok, while the
     second and third were printed as blanks.  */
  warning (OPT_Wstrict_aliasing,
	   "%Hlikely type-punning may break strict-aliasing rules: "
	   "object %<%s%s%> of main type %qT is referenced at or around "
	   "%s:%d and may be "
	   "aliased to object %<%s%s%> of main type %qT which is referenced "
	   "at or around %s:%d.",
	   &alias_loc,
	   get_maybe_star_prefix (object1, is_ptr1),
	   name1, get_otype (object1, is_ptr1),
	   LOCATION_FILE (ref1_loc), LOCATION_LINE (ref1_loc),
	   get_maybe_star_prefix (object2, is_ptr2),
	   name2, get_otype (object2, is_ptr2),
	   LOCATION_FILE (ref2_loc), LOCATION_LINE (ref2_loc));

  return true;
}