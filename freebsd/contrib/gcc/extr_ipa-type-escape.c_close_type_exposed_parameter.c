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

/* Variables and functions */
 int /*<<< orphan*/  EXPOSED_PARAMETER ; 
 scalar_t__ FIELD_DECL ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int TYPE_UID (scalar_t__) ; 
 int /*<<< orphan*/  been_there_done_that ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_type (scalar_t__) ; 
 int /*<<< orphan*/  mark_interesting_type (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_type_exposed_parameter (tree type)
{
  tree field;
  int uid;

  type = get_canon_type (type, false, false);
  if (!type)
    return;
  uid = TYPE_UID (type);
  gcc_assert (!POINTER_TYPE_P (type));

  if (bitmap_bit_p (been_there_done_that, uid))
    return;
  bitmap_set_bit (been_there_done_that, uid);

  /* If the field is a struct or union type, mark all of the
     subfields.  */
  for (field = TYPE_FIELDS (type);
       field;
       field = TREE_CHAIN (field))
    {
      tree field_type;

      if (TREE_CODE (field) != FIELD_DECL)
	continue;

      field_type = get_canon_type (TREE_TYPE (field), false, false);
      mark_interesting_type (field_type, EXPOSED_PARAMETER);

      /* Only recurse for non pointer types of structures and unions.  */
      if (ipa_type_escape_star_count_of_interesting_type (field_type) == 0) 
	close_type_exposed_parameter (field_type);
    }
}