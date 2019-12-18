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
typedef  scalar_t__ TYPE_VALUES ;

/* Variables and functions */
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_DECL (scalar_t__) ; 
 int /*<<< orphan*/  enum_type ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_and_check_tag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ make_anon_name () ; 
 scalar_t__ make_node (scalar_t__) ; 
 scalar_t__ pushtag (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_current ; 

tree
start_enum (tree name)
{
  tree enumtype;

  gcc_assert (TREE_CODE (name) == IDENTIFIER_NODE);

  /* If this is the real definition for a previous forward reference,
     fill in the contents in the same object that used to be the
     forward reference.  */

  enumtype = lookup_and_check_tag (enum_type, name,
				   /*tag_scope=*/ts_current,
				   /*template_header_p=*/false);

  if (enumtype != NULL_TREE && TREE_CODE (enumtype) == ENUMERAL_TYPE)
    {
      error ("multiple definition of %q#T", enumtype);
      error ("%Jprevious definition here", TYPE_MAIN_DECL (enumtype));
      /* Clear out TYPE_VALUES, and start again.  */
      TYPE_VALUES (enumtype) = NULL_TREE;
    }
  else
    {
      /* In case of error, make a dummy enum to allow parsing to
	 continue.  */
      if (enumtype == error_mark_node)
	name = make_anon_name ();

      enumtype = make_node (ENUMERAL_TYPE);
      enumtype = pushtag (name, enumtype, /*tag_scope=*/ts_current);
    }

  return enumtype;
}