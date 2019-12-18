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
struct objfile {int dummy; } ;
struct dwarf2_cu {struct objfile* objfile; } ;
struct die_info {scalar_t__ tag; int /*<<< orphan*/  type; struct die_info* child; } ;

/* Variables and functions */
 scalar_t__ DW_TAG_inheritance ; 
 scalar_t__ DW_TAG_member ; 
 scalar_t__ DW_TAG_variable ; 
 char* TYPE_TAG_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_is_declaration (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  new_symbol (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  process_die (struct die_info*,struct dwarf2_cu*) ; 
 char const* processing_current_prefix ; 
 struct die_info* sibling_die (struct die_info*) ; 

__attribute__((used)) static void
process_structure_scope (struct die_info *die, struct dwarf2_cu *cu)
{
  struct objfile *objfile = cu->objfile;
  const char *previous_prefix = processing_current_prefix;
  struct die_info *child_die = die->child;

  if (TYPE_TAG_NAME (die->type) != NULL)
    processing_current_prefix = TYPE_TAG_NAME (die->type);

  /* NOTE: carlton/2004-03-16: GCC 3.4 (or at least one of its
     snapshots) has been known to create a die giving a declaration
     for a class that has, as a child, a die giving a definition for a
     nested class.  So we have to process our children even if the
     current die is a declaration.  Normally, of course, a declaration
     won't have any children at all.  */

  while (child_die != NULL && child_die->tag)
    {
      if (child_die->tag == DW_TAG_member
	  || child_die->tag == DW_TAG_variable
	  || child_die->tag == DW_TAG_inheritance)
	{
	  /* Do nothing.  */
	}
      else
	process_die (child_die, cu);

      child_die = sibling_die (child_die);
    }

  if (die->child != NULL && ! die_is_declaration (die, cu))
    new_symbol (die, die->type, cu);

  processing_current_prefix = previous_prefix;
}