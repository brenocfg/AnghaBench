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
 int /*<<< orphan*/  CLASSTYPE_PRIMARY_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_VFIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_simple_base_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
build_vfield_ref (tree datum, tree type)
{
  tree vfield, vcontext;

  if (datum == error_mark_node)
    return error_mark_node;

  /* First, convert to the requested type.  */
  if (!same_type_ignoring_top_level_qualifiers_p (TREE_TYPE (datum), type))
    datum = convert_to_base (datum, type, /*check_access=*/false,
			     /*nonnull=*/true);

  /* Second, the requested type may not be the owner of its own vptr.
     If not, convert to the base class that owns it.  We cannot use
     convert_to_base here, because VCONTEXT may appear more than once
     in the inheritance hierarchy of TYPE, and thus direct conversion
     between the types may be ambiguous.  Following the path back up
     one step at a time via primary bases avoids the problem.  */
  vfield = TYPE_VFIELD (type);
  vcontext = DECL_CONTEXT (vfield);
  while (!same_type_ignoring_top_level_qualifiers_p (vcontext, type))
    {
      datum = build_simple_base_path (datum, CLASSTYPE_PRIMARY_BINFO (type));
      type = TREE_TYPE (datum);
    }

  return build3 (COMPONENT_REF, TREE_TYPE (vfield), datum, vfield, NULL_TREE);
}