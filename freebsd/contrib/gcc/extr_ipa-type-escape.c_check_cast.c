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
#define  CT_DOWN 131 
#define  CT_SIDEWAYS 130 
#define  CT_UP 129 
#define  CT_USELESS 128 
 scalar_t__ DECL_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_UID (scalar_t__) ; 
 int /*<<< orphan*/  FULL_ESCAPE ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_cast_type (scalar_t__,scalar_t__) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_type (scalar_t__) ; 
 int /*<<< orphan*/  mark_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  results_of_malloc ; 

__attribute__((used)) static void
check_cast (tree to_type, tree from) 
{
  tree from_type = get_canon_type (TREE_TYPE (from), false, false);
  bool to_interesting_type, from_interesting_type;

  to_type = get_canon_type (to_type, false, false);
  if (!from_type || !to_type || from_type == to_type)
    return;

  to_interesting_type = 
    ipa_type_escape_star_count_of_interesting_type (to_type) >= 0;
  from_interesting_type = 
    ipa_type_escape_star_count_of_interesting_type (from_type) >= 0;

  if (to_interesting_type) 
    if (from_interesting_type)
      {
	/* Both types are interesting. This can be one of four types
	   of cast: useless, up, down, or sideways.  We do not care
	   about up or useless.  Sideways casts are always bad and
	   both sides get marked as escaping.  Downcasts are not
	   interesting here because if type is marked as escaping, all
	   of its subtypes escape.  */
	switch (check_cast_type (to_type, from_type)) 
	  {
	  case CT_UP:
	  case CT_USELESS:
	  case CT_DOWN:
	    break;

	  case CT_SIDEWAYS:
	    mark_type (to_type, FULL_ESCAPE);
	    mark_type (from_type, FULL_ESCAPE);
	    break;
	  }
      }
    else
      {
	/* If this is a cast from the local that is a result from a
	   call to malloc, do not mark the cast as bad.  */
	if (DECL_P (from) && !bitmap_bit_p (results_of_malloc, DECL_UID (from)))
	  mark_type (to_type, FULL_ESCAPE);
      }
  else if (from_interesting_type)
    mark_type (from_type, FULL_ESCAPE);
}