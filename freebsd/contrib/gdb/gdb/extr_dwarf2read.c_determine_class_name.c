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
struct dwarf2_cu {int dummy; } ;
struct die_info {scalar_t__ tag; struct die_info* child; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ DW_TAG_subprogram ; 
 char* class_name_from_physname (int /*<<< orphan*/ ) ; 
 char* determine_prefix (struct die_info*,struct dwarf2_cu*) ; 
 struct die_info* die_specification (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dwarf2_linkage_name (struct die_info*,struct dwarf2_cu*) ; 
 char* dwarf2_name (struct die_info*,struct dwarf2_cu*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 char* processing_current_prefix ; 
 int /*<<< orphan*/  processing_has_namespace_info ; 
 struct die_info* sibling_die (struct die_info*) ; 
 char* typename_concat (char*,char const*) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static char *
determine_class_name (struct die_info *die, struct dwarf2_cu *cu)
{
  struct cleanup *back_to = NULL;
  struct die_info *spec_die = die_specification (die, cu);
  char *new_prefix = NULL;

  /* If this is the definition of a class that is declared by another
     die, then processing_current_prefix may not be accurate; see
     read_func_scope for a similar example.  */
  if (spec_die != NULL)
    {
      char *specification_prefix = determine_prefix (spec_die, cu);
      processing_current_prefix = specification_prefix;
      back_to = make_cleanup (xfree, specification_prefix);
    }

  /* If we don't have namespace debug info, guess the name by trying
     to demangle the names of members, just like we did in
     add_partial_structure.  */
  if (!processing_has_namespace_info)
    {
      struct die_info *child;

      for (child = die->child;
	   child != NULL && child->tag != 0;
	   child = sibling_die (child))
	{
	  if (child->tag == DW_TAG_subprogram)
	    {
	      new_prefix = class_name_from_physname (dwarf2_linkage_name
						     (child, cu));

	      if (new_prefix != NULL)
		break;
	    }
	}
    }

  if (new_prefix == NULL)
    {
      const char *name = dwarf2_name (die, cu);
      new_prefix = typename_concat (processing_current_prefix,
				    name ? name : "<<anonymous>>");
    }

  if (back_to != NULL)
    do_cleanups (back_to);

  return new_prefix;
}