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
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int TYPE_UID (scalar_t__) ; 
 int /*<<< orphan*/  been_there_done_that ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_or_array_type (scalar_t__) ; 
 int /*<<< orphan*/  subtype_map_for_uid (int,int) ; 

__attribute__((used)) static void
close_type_seen (tree type)
{
  tree field;
  int i, uid;
  tree binfo, base_binfo;

  /* See thru all pointer tos and array ofs. */
  type = get_canon_type (type, true, true);
  if (!type)
    return;

  uid = TYPE_UID (type);

  if (bitmap_bit_p (been_there_done_that, uid))
    return;
  bitmap_set_bit (been_there_done_that, uid);

  /* If we are doing a language with a type hierarchy, mark all of
     the superclasses.  */
  if (TYPE_BINFO (type)) 
    for (binfo = TYPE_BINFO (type), i = 0;
	 BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
      {
	tree binfo_type = BINFO_TYPE (base_binfo);
	bitmap subtype_map = subtype_map_for_uid 
	  (TYPE_UID (TYPE_MAIN_VARIANT (binfo_type)), true);
	bitmap_set_bit (subtype_map, uid);
	close_type_seen (get_canon_type (binfo_type, true, true));
      }
      
  /* If the field is a struct or union type, mark all of the
     subfields.  */
  for (field = TYPE_FIELDS (type);
       field;
       field = TREE_CHAIN (field))
    {
      tree field_type;
      if (TREE_CODE (field) != FIELD_DECL)
	continue;

      field_type = TREE_TYPE (field);
      if (ipa_type_escape_star_count_of_interesting_or_array_type (field_type) >= 0)
	close_type_seen (get_canon_type (field_type, true, true));
    }
}