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
typedef  scalar_t__ base_kind ;

/* Variables and functions */
 scalar_t__ BINFO_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  ba_check ; 
 int /*<<< orphan*/  ba_unique ; 
 scalar_t__ binfo_from_vbase (scalar_t__) ; 
 scalar_t__ bk_ambig ; 
 scalar_t__ bk_inaccessible ; 
 scalar_t__ bk_via_virtual ; 
 int /*<<< orphan*/  convert_to_integer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_not_base_type (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ lookup_base (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ptrdiff_type_node ; 
 scalar_t__ same_type_ignoring_top_level_qualifiers_p (scalar_t__,scalar_t__) ; 
 scalar_t__ size_diffop (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  size_zero_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_delta_difference (tree from, tree to,
		      bool allow_inverse_p,
		      bool c_cast_p)
{
  tree binfo;
  base_kind kind;
  tree result;

  /* Assume no conversion is required.  */
  result = integer_zero_node;
  binfo = lookup_base (to, from, c_cast_p ? ba_unique : ba_check, &kind);
  if (kind == bk_inaccessible || kind == bk_ambig)
    error ("   in pointer to member function conversion");
  else if (binfo)
    {
      if (kind != bk_via_virtual)
	result = BINFO_OFFSET (binfo);
      else
	{
	  tree virt_binfo = binfo_from_vbase (binfo);

	  /* This is a reinterpret cast, we choose to do nothing.  */
	  if (allow_inverse_p)
	    warning (0, "pointer to member cast via virtual base %qT",
		     BINFO_TYPE (virt_binfo));
	  else
	    error ("pointer to member conversion via virtual base %qT",
		   BINFO_TYPE (virt_binfo));
	}
    }
  else if (same_type_ignoring_top_level_qualifiers_p (from, to))
    /* Pointer to member of incomplete class is permitted*/;
  else if (!allow_inverse_p)
    {
      error_not_base_type (from, to);
      error ("   in pointer to member conversion");
    }
  else
    {
      binfo = lookup_base (from, to, c_cast_p ? ba_unique : ba_check, &kind);
      if (binfo)
	{
	  if (kind != bk_via_virtual)
	    result = size_diffop (size_zero_node, BINFO_OFFSET (binfo));
	  else
	    {
	      /* This is a reinterpret cast, we choose to do nothing.  */
	      tree virt_binfo = binfo_from_vbase (binfo);

	      warning (0, "pointer to member cast via virtual base %qT",
		       BINFO_TYPE (virt_binfo));
	    }
	}
    }

  return fold_if_not_in_template (convert_to_integer (ptrdiff_type_node,
						      result));
}